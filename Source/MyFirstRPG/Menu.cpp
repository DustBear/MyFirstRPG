// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

UMenu::UMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UMenu::NativeConstruct()
{
    Super::NativeConstruct();

    BuildInventory();
}

void UMenu::BuildInventory()
{
    int32 Row = 0;
    int32 Col = 0;
    check(Player != nullptr);

    for (int i = 0; i < RowSize * ColSize; i++)
    {
        // 아이콘 생성
        UInventoryIcon* NewInventoryIcon = CreateWidget<UInventoryIcon>(GetWorld(), InventoryIcon);
        check(NewInventoryIcon != nullptr);

        // 인벤토리에 있는 아이템의 ItemInfo를 아이콘에 적용
        if (i < Player->Inventory.Num())
        {
            NewInventoryIcon->ItemInfo = Player->Inventory[i];
        }

        // 아이콘을 인벤토리에 적용
        check(InventoryGridPannel != nullptr);
        InventoryGridPannel->AddChildToUniformGrid(NewInventoryIcon, Row, Col);

        if (Col >= RowSize - 1)
        {
            Col = 0;
            Row++;
        }
        else
        {
            Col++;
        }
    }
}