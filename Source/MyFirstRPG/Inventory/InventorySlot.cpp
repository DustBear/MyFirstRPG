// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySlot.h"
#include "Player/MyFirstRPGCharacter.h"

void UInventorySlot::OnClickEvent()
{
    if (ItemCount == 0)
    {
        return;
    }

    // 더블 클릭 시 아이템 사용
    ClickCount++;
    if (ClickCount == 2)
    {
        AMyFirstRPGCharacter *Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (Player == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Player is nullptr"));
            return;
        }
        Player->UseItem(ItemInfo, SlotIndex);

        ClickCount = 0;
    }
}

void UInventorySlot::OnReleaseEvent()
{
    if (ItemCount == 0)
    {
        return;
    }

    // 딜레이 후 ClickCount를 0으로 설정
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
    {
        ClickCount = 0;
    }), ClickDelayTime, false);
}

void UInventorySlot::UpdateButtonImage()
{
    if (Button == nullptr)
    {
        SetButton();
    }

    FButtonStyle ButtonStyle;
    FSlateBrush SlateBrush;

    // 버튼에 아이템 이미지 적용
    SlateBrush.SetResourceObject(ItemInfo.ItemImage);
    ButtonStyle.Normal = SlateBrush;
    ButtonStyle.Pressed = SlateBrush;
    
    // 버튼에 색 적용
    SlateBrush.TintColor = FSlateColor(FColor(0.1, 0.1, 0.1));
    ButtonStyle.Hovered = SlateBrush;
    
    Button->SetStyle(ButtonStyle);
}

//////////////////////////////////////////////////////////////////////////
// Getter Setter

void UInventorySlot::AddItemCount(const int32 Amount)
{
    ItemCount += Amount;
}

const int32 UInventorySlot::GetItemCount() const
{
    return ItemCount;
}

void UInventorySlot::SetSlotIndex(const int32 Index)
{
    SlotIndex = Index;
}

void UInventorySlot::SetItemInfo(const FItemInfo& NewItemInfo)
{
    ItemInfo = NewItemInfo;
}

const FItemInfo &UInventorySlot::GetItemInfo() const
{
    return ItemInfo;
}