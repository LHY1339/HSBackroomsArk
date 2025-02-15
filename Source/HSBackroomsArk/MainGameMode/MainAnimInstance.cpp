// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "HSBackroomsArk/Physical/MainStepPhysicalMaterial.h"
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
	IsCrouch=Character->IsCrouch;
}

void UMainAnimInstance::AnimNotify_LeftStep(UAnimNotify* Notify)
{
	__StepNotify("foot_l");
}

void UMainAnimInstance::AnimNotify_RightStep(UAnimNotify* Notify)
{
	__StepNotify("foot_r");
}

void UMainAnimInstance::__CalculateSmooth()
{
	LerpSpeed = UKismetMathLibrary::Abs(Speed - Character->Speed) * (1.0f / Character->ServerDeltaTime);
	LerpDirection = Character->RoundDelta(Direction, Character->Direction) * (1.0f / Character->ServerDeltaTime);
	LerpPitch = UKismetMathLibrary::Abs(Pitch - Character->Pitch) * (1.0f / Character->ServerDeltaTime);
}

void UMainAnimInstance::__StepNotify(FName Socket)
{
	if (!Character)
	{
		Character=Cast<AMainCharacter>(TryGetPawnOwner());
		return;
	}
	FVector start;
	if (GetOwningComponent()->ComponentHasTag("FPP"))
	{
		if (!Character->IsLocallyControlled())
		{
			return;
		}
		start=Character->SK_First->GetSocketLocation(Socket);
	}
	if (GetOwningComponent()->ComponentHasTag("TPP"))
	{
		if (Character->IsLocallyControlled())
		{
			return;
		}
		start=Character->SK_Third->GetSocketLocation(Socket);
	}
	FHitResult hit;
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		start+FVector(0.0f,0.0f,50.0f),
		start-FVector(0.0f,0.0f,50.0f),
		TraceTypeQuery1,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForDuration,
		hit,
		true
		);
	
	if (!hit.bBlockingHit)
	{
		return;
	}
	UMainStepPhysicalMaterial* phymat=Cast<UMainStepPhysicalMaterial>(hit.PhysMaterial);
	if (!phymat||!phymat->StepSound)
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(
	GetWorld(),
	phymat->StepSound,
	Character->GetActorLocation(),
	Character->GetActorRotation()
	);
}
