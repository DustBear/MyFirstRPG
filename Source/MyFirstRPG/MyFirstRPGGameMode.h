// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Inventory.h"

#include "MyFirstRPGGameMode.generated.h"

UCLASS(minimalapi)
class AMyFirstRPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AMyFirstRPGGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BP_Inventory;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	UPROPERTY()
	UInventory* Inventory;
};



