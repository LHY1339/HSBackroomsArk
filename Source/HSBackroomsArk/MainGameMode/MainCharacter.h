// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class AMainGameStateBase;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class HSBACKROOMSARK_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//override
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	//Axis
	void AxisMoveForward(float Value);
	void AxisMoveRight(float Value);
	void AxisLookUp(float Value);
	void AxisLookRight(float Value);
	
private:
	//Init
	void __InitComponent();

	//Tick
	void __GetServerDeltaTime();
	void __SmoothPlayerTransform();

public:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_First;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_Third;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SPR_First;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CAM_First;

	UPROPERTY(Replicated)
	FVector PlayerLocation;

private:
	float ServerDeltaTime;

	AMainGameStateBase* GameState;
};
