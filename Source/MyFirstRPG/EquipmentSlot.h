// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
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
	/** C++�� Button������ ��� ����Ʈ�� Button�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetButton();

	/** ������ �����ϴ� ������ ������ ���� �� ��ư �̹����� ���� */
	UFUNCTION()
	void UpdateItemInfo(const FItemInfo& NewItemInfo);

	UFUNCTION()
	const FItemInfo GetItemInfo() const;
	
	UPROPERTY(BlueprintReadWrite)
    UButton* Button;

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

private:
	/** ������ Ŭ���� Ƚ�� */
	UPROPERTY()
	int32 ClickCount;

	UPROPERTY()
	FItemInfo ItemInfo;
};
