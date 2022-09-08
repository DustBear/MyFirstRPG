// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyFirstRPGCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ItemInfo 데이터 테이블 불러오기
	const FString ItemInfoPath = TEXT("DataTable'/Game/Items/DT_ItemInfo.DT_ItemInfo'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemInfo(*ItemInfoPath);
	if (DT_ItemInfo.Succeeded())
	{
		UE_LOG(LogTemp, Display, TEXT("Success: load DT_ItemInfo"));
		DataTable = DT_ItemInfo.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail: load DT_ItemInfo"));
	}
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	// ItemInfo 데이터 테이블에서 RowName에 해당하는 Row 찾기
	UEnum* ItemNames = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemNames"), true);
	FName ItemName = FName(ItemNames->GetNameStringByValue((int32)RowName));
	
	ItemInfo = *DataTable->FindRow<FItemInfo>(ItemName, TEXT(""));
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Interact()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyFirstRPGCharacter* PlayerScript = Cast<AMyFirstRPGCharacter>(Player);
	PlayerScript->PickUpItem(ItemInfo);
	Destroy();
}
