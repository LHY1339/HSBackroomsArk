// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "MainGameStateBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HSBackroomsArk/Interface/IDetail.h"
#include "HSBackroomsArk/Interface/IHold.h"
#include "HSBackroomsArk/Interface/IInteract.h"
#include "HSBackroomsArk/Interface/IRPC.h"
#include "HSBackroomsArk/Interface/IView.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Widget/UW_Main.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	__InitComponent();
	BagList.Init(nullptr,4);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	__BeginBindEvent();
	__BeginWidget();
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
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&AMainCharacter::ActionInteractPress);
	PlayerInputComponent->BindAction("Walk",IE_Pressed,this,&AMainCharacter::ActionWalkPress);
	PlayerInputComponent->BindAction("Walk",IE_Released,this,&AMainCharacter::ActionWalkRelease);
	PlayerInputComponent->BindAction("HoldFirst",IE_Pressed,this,&AMainCharacter::ActionHoldFirstPress);
	PlayerInputComponent->BindAction("HoldSecond",IE_Pressed,this,&AMainCharacter::ActionHoldSecondPress);
	PlayerInputComponent->BindAction("HoldThird",IE_Pressed,this,&AMainCharacter::ActionHoldThirdPress);
	PlayerInputComponent->BindAction("HoldFourth",IE_Pressed,this,&AMainCharacter::ActionHoldFourthPress);
	PlayerInputComponent->BindAction("UseFirst",IE_Pressed,this,&AMainCharacter::ActionUseFirstPress);
	PlayerInputComponent->BindAction("UseSecond",IE_Pressed,this,&AMainCharacter::ActionUseSecondPress);
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
	DOREPLIFETIME(AMainCharacter,BagList);
	DOREPLIFETIME(AMainCharacter,HoldAsset);
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

void AMainCharacter::ActionInteractPress()
{
	for (int32 i=0;i<DetailActorList.Num();i++)
	{
		Interact(DetailActorList[i]);
	}
}

void AMainCharacter::ActionWalkPress()
{
	SetMaxWalkSpeed(200.0f);
}

void AMainCharacter::ActionWalkRelease()
{
	SetMaxWalkSpeed(400.0f);
}

void AMainCharacter::ActionHoldFirstPress()
{
	Hold(0);
}

void AMainCharacter::ActionHoldSecondPress()
{
	Hold(1);
}

void AMainCharacter::ActionHoldThirdPress()
{
	Hold(2);
}

void AMainCharacter::ActionHoldFourthPress()
{
	Hold(3);
}

void AMainCharacter::ActionUseFirstPress()
{
	if (!HoldAsset)
	{
		return;
	}
	IIHold* Interface=Cast<IIHold>(HoldAsset);
	if(Interface)
	{
		Interface->Execute_OnUseFirst(HoldAsset,this);
	}
}

void AMainCharacter::ActionUseSecondPress()
{
	if (!HoldAsset)
	{
		return;
	}
	IIHold* Interface=Cast<IIHold>(HoldAsset);
	if(Interface)
	{
		Interface->Execute_OnUseSecond(HoldAsset,this);
	}
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

void AMainCharacter::BOX_ViewBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIView* Interface=Cast<IIView>(OtherActor);
	if (Interface)
	{
		Interface->Execute_OnView(OtherActor,this);
	}
}

void AMainCharacter::BOX_ViewEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	IIView* Interface=Cast<IIView>(OtherActor);
	if (Interface)
	{
		Interface->Execute_OnNotView(OtherActor,this);
	}
}

void AMainCharacter::BOX_DetailBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIDetail* Interface=Cast<IIDetail>(OtherActor);
	if (Interface)
	{
		Interface->Execute_OnShowDetail(OtherActor,this);
	}
}

void AMainCharacter::BOX_DetailEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	IIDetail* Interface=Cast<IIDetail>(OtherActor);
	if (Interface)
	{
		Interface->Execute_OnNotShowDetail(OtherActor,this);
	}
}

void AMainCharacter::RunServer_Implementation(AActor* RunActor,int Function)
{
	IIRPC* Interface=Cast<IIRPC>(RunActor);
	if (Interface)
	{
		Interface->Execute_OnRunServer(RunActor,this,Function);
	}
}

void AMainCharacter::RunServerReliable_Implementation(AActor* RunActor,int Function)
{
	IIRPC* Interface=Cast<IIRPC>(RunActor);
	if (Interface)
	{
		Interface->Execute_OnRunServerReliable(RunActor,this,Function);
	}
}

void AMainCharacter::Interact_Server_Implementation(AActor* RunActor, int32 Function)
{
	IIInteract* Interface=Cast<IIInteract>(RunActor);
	if (!Interface)
	{
		return;
	}
	switch (Function)
	{
		case 1:
			Interface->Execute_OnInteract(RunActor,this);
			break;
	}
}

void AMainCharacter::Hold_Server_Implementation(AActor* RunActor, int32 Function)
{
	IIHold* Interface=Cast<IIHold>(RunActor);
	if (!Interface)
	{
		return;
	}
	switch (Function)
	{
	case 1:
		Interface->Execute_OnHold(RunActor,this);
		break;
	case 2:
		Interface->Execute_OnNotHold(RunActor,this);
		break;
	case 3:
		Interface->Execute_OnUseFirst(RunActor,this);
		break;
	case 4:
		Interface->Execute_OnUseSecond(RunActor,this);
		break;
	case 5:
		Interface->Execute_OnDrop(RunActor,this);
		break;
	}
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

void AMainCharacter::Interact(AActor* InteractActor)
{
	Interact_Server(InteractActor,1);
}

void AMainCharacter::OnPawnLeavingGame()
{
	for (int32 i=0;i<BagList.Num();i++)
	{
		if (BagList[i])
		{
			IIHold* Interface=Cast<IIHold>(BagList[i]);
			if (Interface)
			{
				Interface->Execute_OnDrop(BagList[i],this);
			}
		}
	}
	Destroy();
}

void AMainCharacter::Hold(int32 Index)
{
	if (!BagList[Index])
	{
		return;
	}
	Hold_Server(BagList[Index],1);
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

	BOX_View=CreateDefaultSubobject<UBoxComponent>("BOX_View");
	BOX_View->SetupAttachment(RootComponent);

	BOX_Detail=CreateDefaultSubobject<UBoxComponent>("BOX_Detail");
	BOX_Detail->SetupAttachment(RootComponent);
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
	Speed=GetVelocity().Size2D();
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

void AMainCharacter::__BeginWidget()
{
	if (!IsLocallyControlled() || !MainWidgetClass)
	{
		return;
	}
	MainWidget = CreateWidget<UUW_Main>(GetWorld(), MainWidgetClass);
	if (MainWidget)
	{
		MainWidget->AddToViewport(1);
		MainWidget->Character = this;
	}
}

void AMainCharacter::__BeginBindEvent()
{
	BOX_View->OnComponentBeginOverlap.AddDynamic(this,&AMainCharacter::BOX_ViewBeginOverlap);
	BOX_View->OnComponentEndOverlap.AddDynamic(this,&AMainCharacter::BOX_ViewEndOverlap);
	BOX_Detail->OnComponentBeginOverlap.AddDynamic(this,&AMainCharacter::BOX_DetailBeginOverlap);
	BOX_Detail->OnComponentEndOverlap.AddDynamic(this,&AMainCharacter::BOX_DetailEndOverlap);
}

