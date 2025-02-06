// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_First;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SK_Third;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SPR_First;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CAM_First;
	
private:
	//Init
	void __InitComponent();
};
