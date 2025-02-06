// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "MainGameStateBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

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

	if (IsLocallyControlled())
	{
		
	}
	else
	{
		__GetServerDeltaTime();
		__SmoothPlayerTransform();
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::AxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::AxisMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AxisLookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMainCharacter::AxisLookRight);
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainCharacter,PlayerLocation);
}

void AMainCharacter::AxisMoveForward(float Value)
{
	if (Value==0)
	{
		return;
	}
}

void AMainCharacter::AxisMoveRight(float Value)
{
	if (Value==0)
	{
		return;
	}
}

void AMainCharacter::AxisLookUp(float Value)
{
	if (Value==0)
	{
		return;
	}
}

void AMainCharacter::AxisLookRight(float Value)
{
	if (Value==0)
	{
		return;
	}
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

void AMainCharacter::__GetServerDeltaTime()
{
	if (!GameState)
	{
		GameState=Cast<AMainGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	}
	ServerDeltaTime=GameState->ServerDeltaTime;
}

void AMainCharacter::__SmoothPlayerTransform()
{
	
}

