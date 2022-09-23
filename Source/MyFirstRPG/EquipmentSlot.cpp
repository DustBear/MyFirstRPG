// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlot.h"
#include "MyFirstRPGCharacter.h"

void UEquipmentSlot::OnClickEvent()
{
    if (ItemInfo.ItemDataTable.MaxCount == 0)
    {
        return;
    }

    // ���� Ŭ�� �� ������ ����
    ClickCount++;
    if (ClickCount == 2)
    {
        AMyFirstRPGCharacter *Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (Player == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Player is nullptr"));
            return;
        }
        Player->PickUpItem(ItemInfo);

        FItemInfo newItemInfo;
        UpdateItemInfo(newItemInfo);

        ClickCount = 0;
    }
}

void UEquipmentSlot::OnReleaseEvent()
{
    if (ItemInfo.ItemDataTable.MaxCount == 0)
    {
        return;
    }

    // ������ �� ClickCount�� 0���� ����
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
    {
        ClickCount = 0;
    }), ClickDelayTime, false);
}

void UEquipmentSlot::UpdateItemInfo(const FItemInfo& NewItemInfo)
{
    ItemInfo = NewItemInfo;

    FButtonStyle ButtonStyle;
    FSlateBrush SlateBrush;

    // ��ư�� ������ �̹��� ����
    SlateBrush.SetResourceObject(ItemInfo.ItemImage);
    ButtonStyle.Normal = SlateBrush;
    ButtonStyle.Pressed = SlateBrush;
    
    // ��ư�� �� ����
    SlateBrush.TintColor = FSlateColor(FColor(0.1, 0.1, 0.1));
    ButtonStyle.Hovered = SlateBrush;
    
    if (Button == nullptr)
    {
        SetButton();
    }
    Button->SetStyle(ButtonStyle);
}

const FItemInfo UEquipmentSlot::GetItemInfo() const
{
    return ItemInfo;
}