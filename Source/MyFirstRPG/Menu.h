// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyFirstRPGCharacter.h"
#include "InventoryIcon.h"
#include "Components/UniformGridPanel.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMenu(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void BuildInventory();

	UPROPERTY(BlueprintReadWrite)
	AMyFirstRPGCharacter* Player;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	UUniformGridPanel* InventoryGridPannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RowSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ColSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UInventoryIcon> InventoryIcon;
};
