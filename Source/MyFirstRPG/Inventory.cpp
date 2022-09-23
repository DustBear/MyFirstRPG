// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::CreateSlots()
{
    SetInventoryGridPanel();
    int32 Row = 0;
    int32 Col = 0;
    
    for (int i = 0; i < RowSize * ColSize; i++)
    {
        // 슬롯 생성
        UInventoryIcon* InventorySlot = CreateWidget<UInventoryIcon>(GetWorld(), BP_InventorySlot);
        if (InventorySlot == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventorySlot is nullptr!!"));
            return;
        }

        // 생성된 슬롯을 슬롯 배열에 추가
        int32 SlotIndex = InventorySlots.Add(InventorySlot);
        InventorySlot->SetSlotIndex(SlotIndex);
        
        // 생성된 슬롯을 GridPanel에 추가
        InventoryGridPanel->AddChildToUniformGrid(InventorySlot, i / RowSize, i % RowSize);
    }
}

void UInventory::AddItem(const FItemInfo& NewItemInfo)
{
	for (int i = 0; i < RowSize * ColSize; i++)
	{
        // 주운 아이템이 인벤토리에 존재하지 않거나, 최대 보유 개수만큼 있다면
        // 빈 슬롯에 아이템 추가하고 아이템 개수 +1
        if (InventorySlots[i]->GetItemCount() == 0)
        {
            UInventoryIcon *TargetSlot = InventorySlots[i];
            TargetSlot->SetItemInfo(NewItemInfo);
            TargetSlot->UpdateButtonImage();
            TargetSlot->AddItemCount(1);
            return;
        }

        // 주운 아이템이 인벤토리에 존재하고, 최대 보유 개수보다 적게 있다면
        // 해당 슬롯의 아이템 개수 +1
		const FItemInfo& ExistedItemInfo = InventorySlots[i]->GetItemInfo();

		if (ExistedItemInfo.ItemDataTable.Name == NewItemInfo.ItemDataTable.Name
        && InventorySlots[i]->GetItemCount() < ExistedItemInfo.ItemDataTable.MaxCount)
		{
			InventorySlots[i]->AddItemCount(1);
			return;
		}
	}

    UE_LOG(LogTemp, Display, TEXT("Inventory is full"));
}

void UInventory::RemoveItem(int32 SlotIndex)
{
    // 슬롯의 아이템 개수 1 감소
    UInventoryIcon* TargetSlot = InventorySlots[SlotIndex];
    TargetSlot->AddItemCount(-1);

    // 슬롯의 아이템을 모두 사용했다면
    if (TargetSlot->GetItemCount() == 0)
    {
        // 해당 슬롯을 삭제
        InventorySlots.RemoveAt(SlotIndex);

        // 새 슬롯을 끝에 추가
        UInventoryIcon* InventorySlot = CreateWidget<UInventoryIcon>(GetWorld(), BP_InventorySlot);
        if (InventorySlot == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventorySlot is nullptr!!"));
            return;
        }
        InventorySlots.Add(InventorySlot);

        // 변경된 슬롯 배열을 GridPanel에 반영
        InventoryGridPanel->ClearChildren();
        for (int i = 0; i < RowSize * ColSize; i++)
        {
            InventorySlots[i]->SetSlotIndex(i);
            InventoryGridPanel->AddChildToUniformGrid(InventorySlots[i], i / RowSize, i % RowSize);
        }
    }
}

