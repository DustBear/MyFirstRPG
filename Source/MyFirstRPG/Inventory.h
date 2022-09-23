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
