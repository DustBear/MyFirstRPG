// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstRPGGameMode.h"
#include "MyFirstRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyFirstRPGGameMode::AMyFirstRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
