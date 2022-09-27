// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemTypes : uint8
{ None, Health, Mana, Sword, Shield, Key, Resource };

UENUM(BlueprintType)
enum class EItemNames : uint8
{ None, HealthPotion, ManaPotion, RustedSword, IronSword, WoodShield, IronShield };

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemDataTable();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemNames Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemTypes Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Potency;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SelfValue;
};

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()

public:
	FItemInfo();

	UPROPERTY(BlueprintReadOnly)
	FItemDataTable ItemDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AItemBase> ItemBP;
};

UCLASS()
class MYFIRSTRPG_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemNames RowName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItemInfo ItemInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
