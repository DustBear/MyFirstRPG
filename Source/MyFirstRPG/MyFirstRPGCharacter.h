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
// �߰��� ���

public:
	//////////////////////////////////////////////////////////////////////////
	// ĳ���� �ɷ�ġ Getter Setter
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
	// ������ ȹ��, ���

	UFUNCTION()
	/**
	 * �ʿ� ���� �������� �ֿ����� ȣ���
	 * �κ��丮�� ������ �߰���
	 * 
	 * @param ItemInfo ȹ���� ������ ����
	 */
	void PickUpItem(const FItemInfo& ItemInfo);
	
	UFUNCTION()
	/**
	 * �κ��丮�� �ִ� �������� ������� �� ȣ���
	 * �κ��丮���� �������� �Ҹ��Ű�� �������� ������ �´� ȿ���� �÷��̾�� ����
	 * 
	 * @param ItemInfo ����� �������� ����
	 * @param ItemIndex ����� �������� �κ��丮 ���� ��ġ
	 */
	void UseItem(const FItemInfo& ItemInfo, const int32& ItemIndex);

	UFUNCTION()
	/**
	 * ���â���� ��� ������ �� ȣ���
	 * ���â���� ��� �����ϰ� �κ��丮�� ��� �߰���. �÷��̾� Mesh������ ��� ����  
	 * 
	 * @param EquipmentType ������ ����� ����
	 * @param IsChangeSword ��� �����ϴ� ������ ���� �������� Sword�� �ٸ� Sword�� ��ü�ϱ� ��������
	 */
	void TakeOffEquipment(const EItemTypes& EquipmentType, const bool IsChangeSword);

private:
	// ĳ���� �ɷ�ġ
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
	// ������ ���

	UFUNCTION()
	void UsePotion(const EItemTypes &PotionType, const int32 &PotionIndex);

	UFUNCTION()
	void PutOnEquipment(const EItemTypes &EquipmentType, const int32 &EquipementIndex);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SpawnEquipment(UPARAM(ref) AItemBase*& Equipment, const UEquipmentSlot* const EquipmentSlot, const FName SocketName);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void DestroyEquipment(AItemBase* Equipment);

	//////////////////////////////////////////////////////////////////////////
	// ��ȣ�ۿ�

	UFUNCTION()
  	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
  	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Interactables�� �ִ� Actor �� �� �� Actor�� ������ Interact ��Ŵ */
	UFUNCTION()
	void StartInteract();

	// ���� ������ ���� Interatable�� Actor�� ����
	UPROPERTY()
	TArray<AActor*> Interactables;

	// ������ ������ ���� Collider
	UPROPERTY()
    USphereComponent* SphereCollider;

	//////////////////////////////////////////////////////////////////////////
	// UI

	/** WidgetType�� �´� Widget�� Ȱ�� �� ��Ȱ��ȭ*/
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

