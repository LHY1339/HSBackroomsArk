// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "MainCharacter.h"
#include "Chaos/PBDSuspensionConstraintData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (!UKismetSystemLibrary::IsStandalone(GetWorld())&&UKismetSystemLibrary::IsServer(GetWorld()))
	{
		return;
	}
	if (!Character)
	{
		Character=Cast<AMainCharacter>(TryGetPawnOwner());
		return;
	}
	if (!Character->IsLocallyControlled())
	{
		__CalculateSmooth();
		Speed = UKismetMathLibrary::FInterpTo_Constant(Speed, Character->Speed, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), LerpSpeed);
		Direction = UKismetMathLibrary::RInterpTo_Constant(FRotator(0.0f, Direction, 0.0f), FRotator(0.0f, Character->Direction, 0.0f), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), LerpDirection).Yaw;
		Pitch = UKismetMathLibrary::FInterpTo_Constant(Pitch, Character->Pitch, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), LerpPitch);
	}
	else
	{
		Speed = Character->Speed;
		Direction = Character->Direction;
		Pitch = Character->Pitch;
	}

	CameraDelta=Character->CameraDelta;
	Yaw = Character->Yaw;
	HoldAsset=Character->HoldAsset;
}

void UMainAnimInstance::__CalculateSmooth()
{
	LerpSpeed = UKismetMathLibrary::Abs(Speed - Character->Speed) * (1.0f / Character->ServerDeltaTime);
	LerpDirection = Character->RoundDelta(Direction, Character->Direction) * (1.0f / Character->ServerDeltaTime);
	LerpPitch = UKismetMathLibrary::Abs(Pitch - Character->Pitch) * (1.0f / Character->ServerDeltaTime);
}
