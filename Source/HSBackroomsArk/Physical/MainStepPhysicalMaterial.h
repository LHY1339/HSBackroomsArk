// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "MainStepPhysicalMaterial.generated.h"


class USoundBase;

UCLASS()
class HSBACKROOMSARK_API UMainStepPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* StepSound;
};
