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
        // ������ ����
        UInventoryIcon* NewInventoryIcon = CreateWidget<UInventoryIcon>(GetWorld(), InventoryIcon);
        check(NewInventoryIcon != nullptr);

        // �κ��丮�� �ִ� �������� ItemInfo�� �����ܿ� ����
        if (i < Player->Inventory.Num())
        {
            NewInventoryIcon->ItemInfo = Player->Inventory[i];
        }

        // �������� �κ��丮�� ����
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