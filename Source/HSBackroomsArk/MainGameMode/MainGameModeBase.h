// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HSBACKROOMSARK_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainGameModeBase();

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	float ServerDeltaTime=0.0f;
};
