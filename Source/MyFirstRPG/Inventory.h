// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventoryIcon.h"
#include "Components/UniformGridPanel.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** C++의 GridPanel변수에 블루 프린트의 GridPanel을 대입 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetInventoryGridPanel();

	/** 인벤토리를 구성하는 슬롯들 생성. 최초 한 번만 호출 됨. */
	UFUNCTION()
	void CreateSlots();

	/**
	 * 아이템을 획득했음을 인벤토리에 반영
	 * @param NewItemInfo 획득한 아이템의 정보
 	 */
	UFUNCTION()
	void AddItem(const FItemInfo& ItemInfo);

	/**
	 * 아이템이 사용되었음을 인벤토리에 반영
 	 * @param SlotIndex 사용한 아이템이 있는 슬롯의 인덱스
 	 */
	UFUNCTION()
	void RemoveItem(int32 SlotIndex);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RowSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ColSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_InventorySlot;

	UPROPERTY(BlueprintReadWrite)
	UUniformGridPanel* InventoryGridPanel;

private:
	UPROPERTY()
	TArray<UInventoryIcon*> InventorySlots;
};
