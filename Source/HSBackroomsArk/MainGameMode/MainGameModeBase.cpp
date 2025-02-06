// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "Net/UnrealNetwork.h"

AMainGameModeBase::AMainGameModeBase()
{
	PrimaryActorTick.bCanEverTick=true;
	
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ServerDeltaTime=DeltaSeconds;
}

void AMainGameModeBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameModeBase, ServerDeltaTime);
}
