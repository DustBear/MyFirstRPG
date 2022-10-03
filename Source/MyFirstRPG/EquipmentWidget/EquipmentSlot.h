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
	/** C++�� Button������ ��� ����Ʈ�� Button�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetButton();

	/** ������ �����ϴ� ������ ������ ���� �� ��ư �̹����� ���� */
	UFUNCTION()
	void UpdateItemInfo(const FItemInfo& NewItemInfo);

	/** Getter */
	UFUNCTION()
	const FItemInfo GetItemInfo() const;

private:
	/** ��ư Click�� ClickCount ����. ClickCount�� 2�� �Ǹ� ���Կ� �����Ǿ� �ִ� ������ ��� */
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void OnClickEvent();

	/** ��ư Release�� ���� ������ �� ClickCount�� 0���� ���� */
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void OnReleaseEvent();
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UButton* Button;

	// ������ Ŭ���� Ƚ��
	UPROPERTY()
	int32 ClickCount;

	UPROPERTY()
	FItemInfo ItemInfo;

	// ��ư Release �� ClickCount�� 0���� �ʱ�ȭ�ϱ���� �ɸ��� �ð�
	UPROPERTY(EditDefaultsOnly)
	float ClickDelayTime;
};
