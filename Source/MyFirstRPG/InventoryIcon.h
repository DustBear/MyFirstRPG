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
	/** C++의 Button변수에 블루 프린트의 Button을 대입 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetButton();

	/** 버튼의 이미지를 아이템 이미지로 설정 */
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
	/** 버튼 Click시 ClickCount 증가. ClickCount가 2가 되면 슬롯에 보관되어 있는 아이템 사용 */
	UFUNCTION(BlueprintCallable)
	void OnClickEvent();

	/** 버튼 Release시 일정 딜레이 후 ClickCount를 0으로 설정 */
	UFUNCTION(BlueprintCallable)
	void OnReleaseEvent();
	
	/** 버튼 Release 후 ClickCount를 0으로 초기화하기까지 걸리는 시간 */
	UPROPERTY(EditDefaultsOnly)
	float ClickDelayTime;

	UPROPERTY(BlueprintReadWrite)
    UButton* Button;

	UPROPERTY(BlueprintReadOnly)
	FItemInfo ItemInfo;

private:
	/** 인벤토리 내에서 슬롯의 인덱스 */
	UPROPERTY()
	int32 SlotIndex;

	/** 슬롯에 보관되어 있는 아이템의 개수 */
	UPROPERTY()
	int32 ItemCount;

	/** 슬롯을 클릭한 횟수 */
	UPROPERTY()
	int32 ClickCount;
};