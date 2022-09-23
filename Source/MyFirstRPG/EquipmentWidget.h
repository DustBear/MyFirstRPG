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
	/** C++의 SwordSlot변수에 블루 프린트의 SwordSlot을 대입 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetSwordSlot();

	/** C++의 ShieldSlot변수에 블루 프린트의 ShieldSlot을 대입 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetShieldSlot();
	
	UPROPERTY(BlueprintReadWrite)
	UEquipmentSlot* SwordSlot;

	UPROPERTY(BlueprintReadWrite)
	UEquipmentSlot* ShieldSlot;
};
