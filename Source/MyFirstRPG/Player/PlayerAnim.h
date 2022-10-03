// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRPG_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	// true가 되면 플레이어가 Sword를 손에 쥠
	// false가 되면 플레이어가 Sword를 손에서 해제함
	UPROPERTY(BlueprintReadOnly)
	bool IsSwordDrawn;

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFall;

	UPROPERTY()
	APawn* Owner;
};
