// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstRPGGameMode.h"
#include "MyFirstRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AMyFirstRPGGameMode::AMyFirstRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyFirstRPGGameMode::BeginPlay()
{
	Super::BeginPlay();

 	checkf(PlayerHUDClass != nullptr, TEXT("PlayerHUDClass is nullptr"));
 	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	
 	checkf(CurrentWidget != nullptr, TEXT("CurrentWidget is nullptr"));
 	CurrentWidget->AddToViewport();
}