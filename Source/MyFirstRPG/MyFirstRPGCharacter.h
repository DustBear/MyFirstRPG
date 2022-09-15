// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "MyFirstRPGCharacter.generated.h"

UCLASS(config=Game)
class AMyFirstRPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyFirstRPGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	// 플레이어 스탯
	UFUNCTION(BlueprintPure, Category = "Level")
	int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Level")
	void UpdateCurrentLevel();


	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateCurrentHealth(float Health);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const;


	UFUNCTION(BlueprintPure, Category = "Mana")
	float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void UpdateCurrentMana(float Mana);

	UFUNCTION(BlueprintPure, Category = "Mana")
	float GetMaxMana() const;


	UFUNCTION(BlueprintPure, Category = "Exp")
	float GetCurrentExp() const;

	UFUNCTION(BlueprintCallable, Category = "Exp")
	void UpdateCurrentExp(float Exp);

	UFUNCTION(BlueprintPure, Category = "Exp")
	float GetMaxExp() const;

	// 상호작용
	UPROPERTY(EditAnywhere)
    USphereComponent* SphereCollider;

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void PickUpItem(const FItemInfo& ItemInfo);

	UFUNCTION()
  	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
  	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TArray<FItemInfo> Inventory;
	
	UPROPERTY(BlueprintReadOnly)
	FItemInfo ItemSelected;
	
protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void StartInteract();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Menu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<UUserWidget> Menu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu", Meta = (BlueprintProtected = "true"))
	UUserWidget* CurrentWidget;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Stat")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentMana;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxMana;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float CurrentExp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxExp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Strength;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Defense;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 SwordModifier;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 ShieldModifier;

	UPROPERTY()
	TArray<AActor*> Interactables;

	UPROPERTY()
	bool IsMenuOpen;

	UFUNCTION()
	void OnOffMenu();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

