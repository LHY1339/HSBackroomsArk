// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class AMainCharacter;

UCLASS()
class HSBACKROOMSARK_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void __DrawView();

private:
	AMainCharacter* Character;
};
