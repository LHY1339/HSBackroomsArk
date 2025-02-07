// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"

class AMainGameModeBase;

UCLASS()
class HSBACKROOMSARK_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMainGameStateBase();
public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(Replicated)
	float ServerDeltaTime;

private:
	AMainGameModeBase* __GameMode;
};
