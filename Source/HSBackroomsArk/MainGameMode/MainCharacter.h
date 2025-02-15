// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UUW_Main;
class UBoxComponent;
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

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
	void ActionInteractPress();
	void ActionCrouchPress();
	void ActionHoldFirstPress();
	void ActionHoldSecondPress();
	void ActionHoldThirdPress();
	void ActionHoldFourthPress();
	void ActionUseFirstPress();
	void ActionUseSecondPress();

	
public:
	//UFUNCTION
	UFUNCTION(Server,Unreliable)
	void UpdateVariable_Server(float newSpeed,float newDirection,float newPitch,float newYaw,FVector newPlayerLocation,FRotator newPlayerRotation,bool newIsCrouch);

	UFUNCTION()
	void OnRep_PlayerLocation();

	UFUNCTION()
	void OnRep_PlayerRotation();

	UFUNCTION()
	void BOX_ViewBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	UFUNCTION()
	void BOX_ViewEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex
		);

	UFUNCTION()
	void BOX_DetailBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	UFUNCTION()
	void BOX_DetailEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex
		);

	UFUNCTION(Server,Unreliable)
	void RunServer(AActor* RunActor,int Function);

	UFUNCTION(Server,Reliable)
	void RunServerReliable(AActor* RunActor,int Function);

	UFUNCTION(Server,Unreliable)
	void Interact_Server(AActor* RunActor,int32 Function);

	UFUNCTION(Server,Unreliable)
	void Hold_Server(AActor* RunActor,int32 Function);
public:
	//CallForOther
	void SetMaxWalkSpeed(float Value);
	float RoundDelta(float A,float B,float RoundHalf=180.0f);
	void Interact(AActor* InteractActor);
	virtual void OnPawnLeavingGame();
	void Hold(int32 Index);
	
private:
	//Init
	void __InitComponent();

	//Tick
	void __GetServerDeltaTime();
	void __SmoothPlayerTransform();
	void __CalculateVariable();
	void __SmoothCameraFOV();

	//BeginPlay
	void __BeginBindEvent();
	void __BeginWidget();

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

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BOX_View;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BOX_Detail;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_Main> MainWidgetClass;
	
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

	UPROPERTY(Replicated)
	TArray<AActor*> BagList;

	UPROPERTY(Replicated)
	AActor* HoldAsset;

	UPROPERTY(Replicated)
	bool IsCrouch;
	
	float HP=100.0f;
	float SAN=100.0f;
	float Energy=0.0f;
	
	FVector CameraDelta;
	
	float ServerDeltaTime;
	
	TArray<AActor*> ViewActorList;
	TArray<AActor*> DetailActorList;

	UUW_Main* MainWidget;
	
private:
	float LerpRotation;
	float LerpLocation;
	
	AMainGameStateBase* GameState;
};
