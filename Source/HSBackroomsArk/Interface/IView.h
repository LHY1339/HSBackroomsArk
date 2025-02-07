// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IView.generated.h"

UINTERFACE(Blueprintable)
class UIView :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIView
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnView(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnNotView(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTexture2D* GetViewTexture();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector2D GetViewTextureSize();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetViewOffset();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCanView();
};
