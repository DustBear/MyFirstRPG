// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EquipmentSlot.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** C++�� SwordSlot������ ��� ����Ʈ�� SwordSlot�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetSwordSlot();

	/** C++�� ShieldSlot������ ��� ����Ʈ�� ShieldSlot�� ���� */
	UFUNCTION(BlueprintImplementableEvent)
	void SetShieldSlot();
	
	UPROPERTY(BlueprintReadWrite)
	UEquipmentSlot* SwordSlot;

	UPROPERTY(BlueprintReadWrite)
	UEquipmentSlot* ShieldSlot;
};
