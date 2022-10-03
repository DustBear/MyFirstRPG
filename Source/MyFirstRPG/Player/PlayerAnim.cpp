// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnim.h"
#include "GameFramework/PawnMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    if (Owner == nullptr)
    {
        Owner = TryGetPawnOwner();
        if (Owner == nullptr)
        {
            return;
        }
    }

    const FVector& Velocity = Owner->GetVelocity();
    const FRotator& Rotation = Owner->GetActorRotation();

    Speed = Velocity.Length();
    Direction = CalculateDirection(Velocity, Rotation);
    IsFall = Owner->GetMovementComponent()->IsFalling();
}