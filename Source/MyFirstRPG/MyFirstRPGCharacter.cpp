// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstRPGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMyFirstRPGCharacter

AMyFirstRPGCharacter::AMyFirstRPGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyFirstRPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMyFirstRPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMyFirstRPGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AMyFirstRPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AMyFirstRPGCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyFirstRPGCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyFirstRPGCharacter::TouchStopped);

	// 추가한 key bindings
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyFirstRPGCharacter::StartInteract);
}

void AMyFirstRPGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMyFirstRPGCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMyFirstRPGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMyFirstRPGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMyFirstRPGCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyFirstRPGCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyFirstRPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyFirstRPGCharacter::OnOverlapBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AMyFirstRPGCharacter::OnOverlapEnd);

}

void AMyFirstRPGCharacter::StartInteract()
{
	if (Interactables.IsEmpty()) return;
	AActor* Interactable = *Interactables.GetData();
	IInteractInterface* InteractInterface = Cast<IInteractInterface>(Interactable);
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}
}

int AMyFirstRPGCharacter::GetCurrentLevel() const
{
	return CurrentLevel;
}

void AMyFirstRPGCharacter::UpdateCurrentLevel()
{
	CurrentLevel++;
}

float AMyFirstRPGCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void AMyFirstRPGCharacter::UpdateCurrentHealth(float Health)
{
	CurrentHealth += Health;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

float AMyFirstRPGCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

float AMyFirstRPGCharacter::GetCurrentMana() const
{
	return CurrentMana;
}

void AMyFirstRPGCharacter::UpdateCurrentMana(float Mana)
{
	CurrentMana += Mana;
	if (CurrentMana > MaxMana)
	{
		CurrentMana = MaxMana;
	}
}

float AMyFirstRPGCharacter::GetMaxMana() const
{
	return MaxMana;
}

float AMyFirstRPGCharacter::GetCurrentExp() const
{
	return CurrentExp;
}

void AMyFirstRPGCharacter::UpdateCurrentExp(float Exp)
{
	CurrentExp += Exp;
	if (CurrentExp > MaxExp)
	{
		CurrentExp = MaxExp;
	}
}

float AMyFirstRPGCharacter::GetMaxExp() const
{
	return MaxExp;
}

void AMyFirstRPGCharacter::PickUpItem(FItemInfo ItemInfo)
{
	
}

// Interactable한 Actor와 overlap되면 Interactables라는 Array에 그것을 추가
void AMyFirstRPGCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		if (OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			Interactables.AddUnique(OtherActor);
		}
	}
}

void AMyFirstRPGCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		if (OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			Interactables.Remove(OtherActor);
		}
	}
}