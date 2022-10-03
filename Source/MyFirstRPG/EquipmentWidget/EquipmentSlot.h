// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable/Item/ItemBase.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	/** C++의 Button변수에 블루 프린트의 Button을 대입 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetButton();

	/** 슬롯이 저장하는 아이템 정보를 변경 후 버튼 이미지에 적용 */
	UFUNCTION()
	void UpdateItemInfo(const FItemInfo& NewItemInfo);

	/** Getter */
	UFUNCTION()
	const FItemInfo GetItemInfo() const;

private:
	/** 버튼 Click시 ClickCount 증가. ClickCount가 2가 되면 슬롯에 보관되어 있는 아이템 사용 */
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void OnClickEvent();

	/** 버튼 Release시 일정 딜레이 후 ClickCount를 0으로 설정 */
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void OnReleaseEvent();
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UButton* Button;

	// 슬롯을 클릭한 횟수
	UPROPERTY()
	int32 ClickCount;

	UPROPERTY()
	FItemInfo ItemInfo;

	// 버튼 Release 후 ClickCount를 0으로 초기화하기까지 걸리는 시간
	UPROPERTY(EditDefaultsOnly)
	float ClickDelayTime;
};
