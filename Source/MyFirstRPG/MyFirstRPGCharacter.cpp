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
	PlayerInputComponent->BindAction<FOnOffWidgetDelegate>("Inventory", IE_Pressed, this, &AMyFirstRPGCharacter::OnOffWidget, EWidgetTypes::Inventory);
	PlayerInputComponent->BindAction<FOnOffWidgetDelegate>("EquipmentWidget", IE_Pressed, this, &AMyFirstRPGCharacter::OnOffWidget, EWidgetTypes::EquipmentWidget);
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

	// SphereCollider에 overlap되었을 때 함수 호출
	SphereCollider = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyFirstRPGCharacter::OnOverlapBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AMyFirstRPGCharacter::OnOverlapEnd);

	// 인벤토리 생성
	Inventory = CreateWidget<UInventory>(GetWorld(), BP_Inventory);
	Inventory->CreateSlots();

	// 장비창 생성
	EquipmentWidget = CreateWidget<UEquipmentWidget>(GetWorld(), BP_EquipmentWidget);
}

//////////////////////////////////////////////////////////////////////////
// 아이템

void AMyFirstRPGCharacter::PickUpItem(const FItemInfo& ItemInfo)
{
	Inventory->AddItem(ItemInfo);
}

void AMyFirstRPGCharacter::UseItem(const FItemInfo& ItemInfo, int32 ItemIndex)
{
	switch (ItemInfo.ItemDataTable.Type)
	{
		case EItemTypes::Health:
			RestoreHealth(ItemInfo.ItemDataTable.Potency);
			break;
		case EItemTypes::Mana:
			RestoreMana(ItemInfo.ItemDataTable.Potency);
			break;
		case EItemTypes::Sword:
			ChangeSword(ItemInfo);
			break;
		case EItemTypes::Shield:
			ChangeShield(ItemInfo);
			break;
		case EItemTypes::Key:
			break;
		case EItemTypes::Resource:
			break;
		default:
			
			break;
	}

	Inventory->RemoveItem(ItemIndex);
}

void AMyFirstRPGCharacter::RestoreHealth(float Amount)
{
	UpdateCurrentHealth(Amount);
}

void AMyFirstRPGCharacter::RestoreMana(float Amount)
{
	UpdateCurrentMana(Amount);
}

void AMyFirstRPGCharacter::ChangeSword(const FItemInfo& NewSwordInfo)
{
	if (EquipmentWidget->SwordSlot == nullptr)
	{
		EquipmentWidget->SetSwordSlot();
	}

	// 장비창 슬롯에 아이템이 이미 있을 경우, 그 아이템을 인벤토리에 추가
	const FItemInfo& ExistedSwordInfo = EquipmentWidget->SwordSlot->GetItemInfo();
	if (ExistedSwordInfo.ItemDataTable.MaxCount != 0)
	{
		PickUpItem(ExistedSwordInfo);
	}

	// 장비창 슬롯에 Sword 추가
	EquipmentWidget->SwordSlot->UpdateItemInfo(NewSwordInfo);
}

void AMyFirstRPGCharacter::ChangeShield(const FItemInfo& NewShieldInfo)
{
	if (EquipmentWidget->ShieldSlot == nullptr)
	{
		EquipmentWidget->SetShieldSlot();
	}

	// 장비창 슬롯에 아이템이 이미 있을 경우, 그 아이템을 인벤토리에 추가
	const FItemInfo& ExistedShieldInfo = EquipmentWidget->ShieldSlot->GetItemInfo();
	if (ExistedShieldInfo.ItemDataTable.MaxCount != 0)
	{
		PickUpItem(ExistedShieldInfo);
	}

	// 장비창 슬롯에 Shield 추가
	EquipmentWidget->ShieldSlot->UpdateItemInfo(NewShieldInfo);
}

//////////////////////////////////////////////////////////////////////////
// 상호작용

void AMyFirstRPGCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Interactable한 Actor와 오버랩되면 Interactables에 추가
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
	// Interactable한 Actor와 오버랩이 끝나면 Interactables에서 제거
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		if (OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			Interactables.Remove(OtherActor);
		}
	}
}

void AMyFirstRPGCharacter::StartInteract()
{
	if (Interactables.IsEmpty()) return;

	// Interactables에 있는 Actor 중 맨 앞 Actor를 꺼내서 Interact 시킴
	AActor* Interactable = *Interactables.GetData();
	IInteractInterface* InteractInterface = Cast<IInteractInterface>(Interactable);
	if (InteractInterface != nullptr)
	{
		InteractInterface->Interact();
	}
}

//////////////////////////////////////////////////////////////////////////
// UI
void AMyFirstRPGCharacter::OnOffWidget(EWidgetTypes WidgetType)
{
	// 활성화 또는 비활성화할 위젯 찾기
	UUserWidget* Widget = nullptr;
	switch (WidgetType)
	{
		case EWidgetTypes::Inventory:
			Widget = Inventory;
			break;
		case EWidgetTypes::EquipmentWidget:
			Widget = EquipmentWidget;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Widget is nullptr"));
			return;
	}
	
	// 위젯을 화면에 활성화 또는 비활성화
	if (!Widget->IsInViewport())
	{
		Widget->AddToViewport();
		ActivatedWidgetCount++;
	}
	else
	{
		Widget->RemoveFromViewport();
		ActivatedWidgetCount--;		
	}

	// 화면에 활성화된 위젯의 존재 여부에 따라 커서 활성화 여부, 인풋 모드 설정
	APlayerController* PlayerController = GetLocalViewingPlayerController();
	if (ActivatedWidgetCount == 0)
	{
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}
	else
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, Widget);
	}
}

//////////////////////////////////////////////////////////////////////////
// Getter Setter

const int32 AMyFirstRPGCharacter::GetCurrentLevel() const
{
	return Stat.CurrentLevel;
}

void AMyFirstRPGCharacter::UpdateCurrentLevel()
{
	Stat.CurrentLevel++;
}

const float AMyFirstRPGCharacter::GetCurrentHealth() const
{
	return Stat.CurrentHealth;
}

void AMyFirstRPGCharacter::UpdateCurrentHealth(float Health)
{
	Stat.CurrentHealth += Health;
	if (Stat.CurrentHealth > Stat.MaxHealth)
	{
		Stat.CurrentHealth = Stat.MaxHealth;
	}
}

const float AMyFirstRPGCharacter::GetMaxHealth() const
{
	return Stat.MaxHealth;
}

const float AMyFirstRPGCharacter::GetCurrentMana() const
{
	return Stat.CurrentMana;
}

void AMyFirstRPGCharacter::UpdateCurrentMana(float Mana)
{
	Stat.CurrentMana += Mana;
	if (Stat.CurrentMana > Stat.MaxMana)
	{
		Stat.CurrentMana = Stat.MaxMana;
	}
}

const float AMyFirstRPGCharacter::GetMaxMana() const
{
	return Stat.MaxMana;
}

const float AMyFirstRPGCharacter::GetCurrentExp() const
{
	return Stat.CurrentExp;
}

void AMyFirstRPGCharacter::UpdateCurrentExp(float Exp)
{
	Stat.CurrentExp += Exp;
	if (Stat.CurrentExp > Stat.MaxExp)
	{
		Stat.CurrentExp = Stat.MaxExp;
	}
}

const float AMyFirstRPGCharacter::GetMaxExp() const
{
	return Stat.MaxExp;
}