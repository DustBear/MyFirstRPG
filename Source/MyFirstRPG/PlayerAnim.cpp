// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
    Speed = 0.0;
    Direction = 0.0;
    IsFall = false;
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* Owner = TryGetPawnOwner();
    if (!IsValid(Owner)) return;

    FVector Velocity = Owner->GetVelocity();
    FRotator Rotation = Owner->GetActorRotation();

    Speed = Velocity.Length();
    Direction = CalculateDirection(Velocity, Rotation);
    IsFall = Owner->GetMovementComponent()->IsFalling();
}