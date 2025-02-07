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

	//Action
	void ActionRunPress();
	void ActionRunRelease();
	void ActionJumpPress();
	void ActionJumpRelease();

public:
	//RPC
	UFUNCTION(Server,Unreliable)
	void UpdateVariable_Server(float newSpeed,float newDirection,float newPitch,float newYaw,FVector newPlayerLocation,FRotator newPlayerRotation);

	UFUNCTION()
	void OnRep_PlayerLocation();

	UFUNCTION()
	void OnRep_PlayerRotation();

public:
	//CallForOther
	void SetMaxWalkSpeed(float Value);
	float RoundDelta(float A,float B,float RoundHalf=180.0f);
	
private:
	//Init
	void __InitComponent();

	//Tick
	void __GetServerDeltaTime();
	void __SmoothPlayerTransform();
	void __CalculateVariable();
	void __SmoothCameraFOV();

public:
	//Defaults
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_First;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_Third;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SPR_First;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CAM_First;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* CUR_FOV;

	//Variable
	UPROPERTY(Replicated)
	float Speed=0.0f;
	
	UPROPERTY(Replicated)
	float Direction=0.0f;

	UPROPERTY(Replicated)
	float Pitch=0.0f;

	UPROPERTY(Replicated)
	float Yaw=0.0f;

	UPROPERTY(ReplicatedUsing=OnRep_PlayerLocation)
	FVector PlayerLocation;

	UPROPERTY(ReplicatedUsing=OnRep_PlayerRotation)
	FRotator PlayerRotation;
	
	FVector CameraDelta;

	float ServerDeltaTime;
	
private:
	float LerpRotation;
	float LerpLocation;
	
	AMainGameStateBase* GameState;
};
