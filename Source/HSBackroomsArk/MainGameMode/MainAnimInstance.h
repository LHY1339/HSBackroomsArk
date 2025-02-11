// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

class AMainCharacter;

UCLASS()
class HSBACKROOMSARK_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	void __CalculateSmooth();
	
public:
	UPROPERTY(BlueprintReadOnly)
	float Speed=0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Direction=0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Pitch=0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Yaw=0.0f;

	UPROPERTY(BlueprintReadOnly)
	FVector CameraDelta;

	UPROPERTY(BlueprintReadOnly)
	AActor* HoldAsset;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UAnimationAsset* AnimationAsset;
	
private:
	AMainCharacter* Character;

	float LerpSpeed;
	float LerpDirection;
	float LerpPitch;
};
