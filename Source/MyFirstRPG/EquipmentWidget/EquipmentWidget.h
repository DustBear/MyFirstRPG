// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EquipmentWidget/EquipmentSlot.h"

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
	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = "true"))
	void SetSwordSlot();

	/** C++�� ShieldSlot������ ��� ����Ʈ�� ShieldSlot�� ���� */
	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = "true"))
	void SetShieldSlot();
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEquipmentSlot* SwordSlot;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEquipmentSlot* ShieldSlot;
};
