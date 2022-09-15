// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryIcon.h"

UInventoryIcon::UInventoryIcon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Player = Cast<AMyFirstRPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UInventoryIcon::NativeConstruct()
{
    Super::NativeConstruct();

    FSlateBrush SlateBrush;
    SlateBrush.SetImageSize(FVector2D(32, 32));
    SlateBrush.SetResourceObject(ItemInfo.ItemImage);

    FSlateBrush ColoredSlateBrush;
    ColoredSlateBrush.SetImageSize(FVector2D(32, 32));
    ColoredSlateBrush.SetResourceObject(ItemInfo.ItemImage);
    ColoredSlateBrush.TintColor = FSlateColor(FColor(0.1, 0.1, 0.1));

    FButtonStyle ButtonStyle;
    ButtonStyle.Normal = SlateBrush;
    ButtonStyle.Pressed = SlateBrush;
    ButtonStyle.Hovered = ColoredSlateBrush;

    Button->SetStyle(ButtonStyle);
}

void UInventoryIcon::OnClickEvent()
{
    Player->ItemSelected = ItemInfo;
}