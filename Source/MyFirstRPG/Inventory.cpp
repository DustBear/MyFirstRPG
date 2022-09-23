// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::CreateSlots()
{
    SetInventoryGridPanel();
    int32 Row = 0;
    int32 Col = 0;
    
    for (int i = 0; i < RowSize * ColSize; i++)
    {
        // ���� ����
        UInventoryIcon* InventorySlot = CreateWidget<UInventoryIcon>(GetWorld(), BP_InventorySlot);
        if (InventorySlot == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventorySlot is nullptr!!"));
            return;
        }

        // ������ ������ ���� �迭�� �߰�
        int32 SlotIndex = InventorySlots.Add(InventorySlot);
        InventorySlot->SetSlotIndex(SlotIndex);
        
        // ������ ������ GridPanel�� �߰�
        InventoryGridPanel->AddChildToUniformGrid(InventorySlot, i / RowSize, i % RowSize);
    }
}

void UInventory::AddItem(const FItemInfo& NewItemInfo)
{
	for (int i = 0; i < RowSize * ColSize; i++)
	{
        // �ֿ� �������� �κ��丮�� �������� �ʰų�, �ִ� ���� ������ŭ �ִٸ�
        // �� ���Կ� ������ �߰��ϰ� ������ ���� +1
        if (InventorySlots[i]->GetItemCount() == 0)
        {
            UInventoryIcon *TargetSlot = InventorySlots[i];
            TargetSlot->SetItemInfo(NewItemInfo);
            TargetSlot->UpdateButtonImage();
            TargetSlot->AddItemCount(1);
            return;
        }

        // �ֿ� �������� �κ��丮�� �����ϰ�, �ִ� ���� �������� ���� �ִٸ�
        // �ش� ������ ������ ���� +1
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
    // ������ ������ ���� 1 ����
    UInventoryIcon* TargetSlot = InventorySlots[SlotIndex];
    TargetSlot->AddItemCount(-1);

    // ������ �������� ��� ����ߴٸ�
    if (TargetSlot->GetItemCount() == 0)
    {
        // �ش� ������ ����
        InventorySlots.RemoveAt(SlotIndex);

        // �� ������ ���� �߰�
        UInventoryIcon* InventorySlot = CreateWidget<UInventoryIcon>(GetWorld(), BP_InventorySlot);
        if (InventorySlot == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventorySlot is nullptr!!"));
            return;
        }
        InventorySlots.Add(InventorySlot);

        // ����� ���� �迭�� GridPanel�� �ݿ�
        InventoryGridPanel->ClearChildren();
        for (int i = 0; i < RowSize * ColSize; i++)
        {
            InventorySlots[i]->SetSlotIndex(i);
            InventoryGridPanel->AddChildToUniformGrid(InventorySlots[i], i / RowSize, i % RowSize);
        }
    }
}

