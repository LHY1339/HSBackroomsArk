// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteract.generated.h"

UINTERFACE(Blueprintable)
class UIInteract :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIInteract
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCanInteract();
};
