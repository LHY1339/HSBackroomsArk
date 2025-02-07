// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "MainGameStateBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
		__CalculateVariable();
		UpdateVariable_Server(Speed,Direction,Pitch,Yaw,PlayerLocation,PlayerRotation);
		__SmoothCameraFOV();
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

	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&AMainCharacter::ActionRunPress);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&AMainCharacter::ActionRunRelease);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMainCharacter::ActionJumpPress);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AMainCharacter::ActionJumpRelease);
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AMainCharacter,Speed,COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMainCharacter,Direction,COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMainCharacter,Pitch,COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMainCharacter,Yaw,COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMainCharacter,PlayerLocation,COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMainCharacter,PlayerRotation,COND_SkipOwner);
}

void AMainCharacter::AxisMoveForward(float Value)
{
	if (Value==0)
	{
		return;
	}
	FVector _direction_ = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).Vector();
	AddMovementInput(_direction_, Value);
}

void AMainCharacter::AxisMoveRight(float Value)
{
	if (Value==0)
	{
		return;
	}
	FVector _direction_ = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(_direction_, Value);
}

void AMainCharacter::AxisLookUp(float Value)
{
	if (Value==0)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void AMainCharacter::AxisLookRight(float Value)
{
	if (Value==0)
	{
		return;
	}
	AddControllerYawInput(Value);
}

void AMainCharacter::ActionRunPress()
{
	SetMaxWalkSpeed(600.0f);
}

void AMainCharacter::ActionRunRelease()
{
	SetMaxWalkSpeed(400.0f);
}

void AMainCharacter::ActionJumpPress()
{
	Jump();
}

void AMainCharacter::ActionJumpRelease()
{
	StopJumping();
}

void AMainCharacter::UpdateVariable_Server_Implementation(float newSpeed, float newDirection, float newPitch,
                                                          float newYaw,FVector newPlayerLocation,FRotator newPlayerRotation)
{
	Speed=newSpeed;
	Direction=newDirection;
	Pitch=newPitch;
	Yaw=newYaw;
	PlayerLocation=newPlayerLocation;
	PlayerRotation=newPlayerRotation;
}

void AMainCharacter::OnRep_PlayerLocation()
{
	if (PlayerLocation == GetActorLocation())
	{
		return;
	}
	if (HasAuthority())
	{
		SetActorLocation(PlayerLocation);
		return;
	}
	float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), PlayerLocation);
	LerpLocation = UKismetMathLibrary::Abs((1.0f / ServerDeltaTime) * Distance);
}

void AMainCharacter::OnRep_PlayerRotation()
{
	if (PlayerRotation == GetActorRotation())
	{
		return;
	}
	if (HasAuthority())
	{
		SetActorRotation(PlayerRotation);
		return;
	}
	float Distance = RoundDelta(GetActorRotation().Yaw, PlayerRotation.Yaw);
	LerpRotation = UKismetMathLibrary::Abs((1.0f / ServerDeltaTime) * Distance);
}

void AMainCharacter::SetMaxWalkSpeed(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed=Value;
}

float AMainCharacter::RoundDelta(float A, float B,float RoundHalf)
{
	float value = UKismetMathLibrary::Abs(A - B);
	if (value > RoundHalf)
	{
		value = RoundHalf * 2 - value;
	}
	return value;
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
		GameState=Cast<AMainGameStateBase>(GetWorld()->GetGameState());
		return;
	}
	ServerDeltaTime=GameState->ServerDeltaTime;
}

void AMainCharacter::__SmoothPlayerTransform()
{
	if (HasAuthority())
	{
		return;
	}
	if (PlayerLocation != GetActorLocation())
	{
		FVector ToLocation = UKismetMathLibrary::VInterpTo_Constant(
			GetActorLocation(),
			PlayerLocation,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			LerpLocation
		);
		SetActorLocation(ToLocation);
	}
	if (PlayerRotation != GetActorRotation())
	{
		FRotator ToRotation = UKismetMathLibrary::RInterpTo_Constant(
			GetActorRotation(),
			PlayerRotation,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			LerpRotation
		);
		SetActorRotation(ToRotation);
	}
}

void AMainCharacter::__CalculateVariable()
{
	Speed=GetVelocity().Size();
	Direction=SK_First->GetAnimInstance()->CalculateDirection(GetVelocity(),GetActorRotation());
	FRotator _delta_=UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(),GetActorRotation());
	Pitch=_delta_.Pitch;
	Yaw=_delta_.Yaw;
	
	FVector rtnV;
	FRotator rtnR;
	SK_First->TransformToBoneSpace("root",CAM_First->GetComponentLocation(),CAM_First->GetComponentRotation(),rtnV,rtnR);
	CameraDelta=-rtnV;

	PlayerLocation=GetActorLocation();
	PlayerRotation=GetActorRotation();
}

void AMainCharacter::__SmoothCameraFOV()
{
	if (!CAM_First)
	{
		return;
	}
	CAM_First->SetFieldOfView(CUR_FOV->GetFloatValue(Speed));
}

