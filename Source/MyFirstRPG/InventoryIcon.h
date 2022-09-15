// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ItemBase.h"
#include "Styling/SlateBrush.h"
#include "Kismet/GameplayStatics.h"
#include "MyFirstRPGCharacter.h"
#include "InventoryIcon.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UInventoryIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryIcon(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItemInfo ItemInfo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AMyFirstRPGCharacter* Player;

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite)
    UButton* Button;

	UFUNCTION(BlueprintCallable)
	void OnClickEvent();
};
