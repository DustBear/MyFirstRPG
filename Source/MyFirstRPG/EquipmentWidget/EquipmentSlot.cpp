// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget/EquipmentSlot.h"
#include "Player/MyFirstRPGCharacter.h"

void UEquipmentSlot::OnClickEvent()
{
    if (ItemInfo.ItemDataTable.MaxCount == 0)
    {
        return;
    }

    ClickCount++;
    // 더블 클릭 시
    if (ClickCount == 2)
    {
        AMyFirstRPGCharacter *Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (Player == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Player is nullptr"));
            return;
        }
        
        // 장착된 장비 해제
        Player->TakeOffEquipment(ItemInfo.ItemDataTable.Type, false);

        ClickCount = 0;
    }
}

void UEquipmentSlot::OnReleaseEvent()
{
    if (ItemInfo.ItemDataTable.MaxCount == 0)
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

void UEquipmentSlot::UpdateItemInfo(const FItemInfo& NewItemInfo)
{
    ItemInfo = NewItemInfo;

    FButtonStyle ButtonStyle;
    FSlateBrush SlateBrush;

    // 버튼에 아이템 이미지 적용
    SlateBrush.SetResourceObject(ItemInfo.ItemImage);
    ButtonStyle.Normal = SlateBrush;
    ButtonStyle.Pressed = SlateBrush;
    
    // 버튼에 색 적용
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