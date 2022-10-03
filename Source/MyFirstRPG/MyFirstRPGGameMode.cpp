// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstRPGGameMode.h"
#include "Player/MyFirstRPGCharacter.h"
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

	// BP_PlayerInfo를 생성하여 화면에 활성화
 	UUserWidget* const CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), BP_PlayerInfo);
	if (CurrentWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot create PlayerHUD"));
		return;
	}
 	CurrentWidget->AddToViewport();
}