// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IRPC.generated.h"

UINTERFACE(Blueprintable)
class UIRPC :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIRPC
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRunServer(AMainCharacter* Character,int Function);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRunServerReliable(AMainCharacter* Character,int Function);
};
