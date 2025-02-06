// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"

AMainGameModeBase::AMainGameModeBase()
{
	PrimaryActorTick.bCanEverTick=true;
	
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ServerDeltaTime=DeltaSeconds;
}
