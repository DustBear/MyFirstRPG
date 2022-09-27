// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "Components/Button.h"
#include "Styling/SlateBrush.h"
#include "TimerManager.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryIcon.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UInventoryIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** C++�� Button������ ��� ����Ʈ�� Button�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetButton();

	/** ��ư�� �̹����� ������ �̹����� ���� */
	UFUNCTION()
	void UpdateButtonImage();

	//////////////////////////////////////////////////////////////////////////
	// Getter Setter
	UFUNCTION()
	void AddItemCount(int32 Amount);

	UFUNCTION(BlueprintCallable)
	const int32 GetItemCount() const;

	UFUNCTION()
	void SetSlotIndex(int32 Index);

	UFUNCTION()
	void SetItemInfo(const FItemInfo& NewItemInfo);

	UFUNCTION()
	const FItemInfo& GetItemInfo() const;

protected:
	/** ��ư Click�� ClickCount ����. ClickCount�� 2�� �Ǹ� ���Կ� �����Ǿ� �ִ� ������ ��� */
	UFUNCTION(BlueprintCallable)
	void OnClickEvent();

	/** ��ư Release�� ���� ������ �� ClickCount�� 0���� ���� */
	UFUNCTION(BlueprintCallable)
	void OnReleaseEvent();
	
	/** ��ư Release �� ClickCount�� 0���� �ʱ�ȭ�ϱ���� �ɸ��� �ð� */
	UPROPERTY(EditDefaultsOnly)
	float ClickDelayTime;

	UPROPERTY(BlueprintReadWrite)
    UButton* Button;

	UPROPERTY(BlueprintReadOnly)
	FItemInfo ItemInfo;

private:
	/** �κ��丮 ������ ������ �ε��� */
	UPROPERTY()
	int32 SlotIndex;

	/** ���Կ� �����Ǿ� �ִ� �������� ���� */
	UPROPERTY()
	int32 ItemCount;

	/** ������ Ŭ���� Ƚ�� */
	UPROPERTY()
	int32 ClickCount;
};