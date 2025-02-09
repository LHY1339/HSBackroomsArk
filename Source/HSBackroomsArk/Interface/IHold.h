// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IHold.generated.h"

UINTERFACE(Blueprintable)
class UIHold :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIHold
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHold(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnNotHold(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUseFirst(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUseSecond(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDrop(AMainCharacter* Character);
	
};
