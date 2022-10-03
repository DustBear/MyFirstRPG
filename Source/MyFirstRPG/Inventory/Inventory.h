// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/InventorySlot.h"
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
	/** C++�� GridPanel������ ��� ����Ʈ�� GridPanel�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetInventoryGridPanel();

	/** �κ��丮�� �����ϴ� ���Ե� ����. ���� �� ���� ȣ�� ��. */
	UFUNCTION()
	void CreateSlots();

	/**
	 * �������� ȹ�������� �κ��丮�� �ݿ�
	 * @param NewItemInfo ȹ���� �������� ����
 	 */
	UFUNCTION()
	void AddItem(const FItemInfo& ItemInfo);

	/**
	 * �������� ���Ǿ����� �κ��丮�� �ݿ�
 	 * @param SlotIndex ����� �������� �ִ� ������ �ε���
 	 */
	UFUNCTION()
	void RemoveItem(int32 SlotIndex);

	/** Getter */
	UFUNCTION()
	const FItemInfo& GetItem(int32 SlotIndex) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 RowSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ColSize;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUniformGridPanel* InventoryGridPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> BP_InventorySlot;

	UPROPERTY()
	TArray<UInventorySlot*> InventorySlots;
};
