// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Inventory/Inventory.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFirstRPGGameMode.generated.h"

UCLASS(minimalapi)
class AMyFirstRPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AMyFirstRPGGameMode();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BP_PlayerInfo;
};



