// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	__InitComponent();
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::__InitComponent()
{
	SK_First=CreateDefaultSubobject<USkeletalMeshComponent>("SK_First");
	SK_First->SetupAttachment(RootComponent);

	SK_Third=CreateDefaultSubobject<USkeletalMeshComponent>("SK_Third");
	SK_Third->SetupAttachment(RootComponent);

	SPR_First=CreateDefaultSubobject<USpringArmComponent>("SPR_First");
	SPR_First->SetupAttachment(SK_First,"head");
	
	CAM_First=CreateDefaultSubobject<UCameraComponent>("CAM_First");
	CAM_First->SetupAttachment(SPR_First);
}

