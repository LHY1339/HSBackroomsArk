// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"

#include "MainGameModeBase.h"
#include "Net/UnrealNetwork.h"

AMainGameStateBase::AMainGameStateBase()
{
	PrimaryActorTick.bCanEverTick=true;
}

void AMainGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority())
	{
		return;
	}
	if (!__GameMode)
	{
		__GameMode=Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
		return;
	}
	ServerDeltaTime=__GameMode->ServerDeltaTime;
}

void AMainGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameStateBase, ServerDeltaTime);
}
