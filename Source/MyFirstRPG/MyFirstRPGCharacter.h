// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PlayerAnim.h"
#include "Inventory.h"
#include "EquipmentWidget.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyFirstRPGCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnOffWidgetDelegate, EWidgetTypes);

USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY()

public:
	FCharacterStat() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentExp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SwordModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ShieldModifier;
};

UENUM(BlueprintType)
enum class EWidgetTypes : uint8
{ Inventory, EquipmentWidget};

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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


//////////////////////////////////////////////////////////////////////////
// 추가한 멤버

public:
	//////////////////////////////////////////////////////////////////////////
	// 캐릭터 능력치 Getter Setter
	UFUNCTION(BlueprintPure, Category = "Level")
	const int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Level")
	void UpdateCurrentLevel();


	UFUNCTION(BlueprintPure, Category = "Health")
	const float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateCurrentHealth(float Health);

	UFUNCTION(BlueprintPure, Category = "Health")
	const float GetMaxHealth() const;


	UFUNCTION(BlueprintPure, Category = "Mana")
	const float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void UpdateCurrentMana(float Mana);

	UFUNCTION(BlueprintPure, Category = "Mana")
	const float GetMaxMana() const;


	UFUNCTION(BlueprintPure, Category = "Exp")
	const float GetCurrentExp() const;

	UFUNCTION(BlueprintCallable, Category = "Exp")
	void UpdateCurrentExp(float Exp);

	UFUNCTION(BlueprintPure, Category = "Exp")
	const float GetMaxExp() const;

	//////////////////////////////////////////////////////////////////////////
	// 아이템 획득, 사용

	UFUNCTION()
	/**
	 * 맵에 놓인 아이템을 주웠을때 호출됨
	 * 인벤토리에 아이템 추가함
	 * 
	 * @param ItemInfo 획득한 아이템 정보
	 */
	void PickUpItem(const FItemInfo& ItemInfo);
	
	UFUNCTION()
	/**
	 * 인벤토리에 있는 아이템을 사용했을 때 호출됨
	 * 인벤토리에서 아이템을 소모시키고 아이템의 종류에 맞는 효과를 플레이어에게 적용
	 * 
	 * @param ItemInfo 사용할 아이템의 정보
	 * @param ItemIndex 사용할 아이템의 인벤토리 내의 위치
	 */
	void UseItem(const FItemInfo& ItemInfo, const int32& ItemIndex);

	UFUNCTION()
	/**
	 * 장비창에서 장비를 해제할 때 호출됨
	 * 장비창에서 장비를 제거하고 인벤토리에 장비를 추가함. 플레이어 Mesh에서도 장비를 제거  
	 * 
	 * @param EquipmentType 해제할 장비의 종류
	 * @param IsChangeSword 장비를 해제하는 목적이 현재 착용중인 Sword를 다른 Sword로 교체하기 위함인지
	 */
	void TakeOffEquipment(const EItemTypes& EquipmentType, const bool IsChangeSword);

private:
	// 캐릭터 능력치
	UPROPERTY(EditDefaultsOnly)
	FCharacterStat Stat;

	UPROPERTY()
	UPlayerAnim* PlayerAnim;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AItemBase* Sword;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AItemBase* Shield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCollisionProfileName NoCollision;

	//////////////////////////////////////////////////////////////////////////
	// 아이템 사용

	UFUNCTION()
	void UsePotion(const EItemTypes &PotionType, const int32 &PotionIndex);

	UFUNCTION()
	void PutOnEquipment(const EItemTypes &EquipmentType, const int32 &EquipementIndex);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SpawnEquipment(UPARAM(ref) AItemBase*& Equipment, const UEquipmentSlot* const EquipmentSlot, const FName SocketName);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void DestroyEquipment(AItemBase* Equipment);

	//////////////////////////////////////////////////////////////////////////
	// 상호작용

	UFUNCTION()
  	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
  	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Interactables에 있는 Actor 중 맨 앞 Actor를 꺼내서 Interact 시킴 */
	UFUNCTION()
	void StartInteract();

	// 현재 오버랩 중인 Interatable한 Actor를 보관
	UPROPERTY()
	TArray<AActor*> Interactables;

	// 오버랩 판정을 위한 Collider
	UPROPERTY()
    USphereComponent* SphereCollider;

	//////////////////////////////////////////////////////////////////////////
	// UI

	/** WidgetType에 맞는 Widget을 활성 및 비활성화*/
	UFUNCTION()
	void OnOffWidget(EWidgetTypes WidgetType);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BP_Inventory;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BP_EquipmentWidget;

	UPROPERTY()
	UInventory* Inventory;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEquipmentWidget* EquipmentWidget;

	UPROPERTY()
	int32 ActivatedWidgetCount;
};

