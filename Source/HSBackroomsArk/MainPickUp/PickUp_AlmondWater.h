// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPickUp.h"
#include "PickUp_AlmondWater.generated.h"

/**
 * 
 */
UCLASS()
class HSBACKROOMSARK_API APickUp_AlmondWater : public AMainPickUp
{
	GENERATED_BODY()
public:
	virtual void OnUseFirst_Implementation(AMainCharacter* Character) override;
};
