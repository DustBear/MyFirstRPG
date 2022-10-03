// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Item/ItemBase.h"
#include "Player/MyFirstRPGCharacter.h"

FItemDataTable::FItemDataTable()
: Name(EItemNames::None), Type(EItemTypes::None), MaxCount(0), Potency(0), Price(0), SelfValue(0)
{}

FItemInfo::FItemInfo()
: ItemImage(nullptr)
{
	FItemDataTable EmptyItemDataTable;
	ItemDataTable = EmptyItemDataTable;
}

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ItemInfo 데이터 테이블 불러오기
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemInfo(TEXT("DataTable'/Game/Items/DT_Item.DT_Item'"));
	if (DT_ItemInfo.Succeeded())
	{
		DataTable = DT_ItemInfo.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail: load DT_Item"));
	}
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	// ItemInfo 데이터 테이블에서 RowName에 해당하는 Row 찾기
	const UEnum* const ItemNames = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemNames"), true);
	if (ItemNames == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find EItemNames"));
		return;
	}
	const FName ItemName = FName(ItemNames->GetNameStringByValue((int32)RowName));
	const FItemDataTable* const Row = DataTable->FindRow<FItemDataTable>(ItemName, TEXT(""));
	if (Row == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find ItemDataTable Row"));
		return;
	}
	ItemInfo.ItemDataTable = *Row;
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Interact()
{
	AMyFirstRPGCharacter* const Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Player"));
	}
	Player->PickUpItem(ItemInfo);
	Destroy();
}
