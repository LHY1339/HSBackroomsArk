// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetail.generated.h"

UINTERFACE(Blueprintable)
class UIDetail :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIDetail
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnShowDetail(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnNotShowDetail(AMainCharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTexture2D* GetDetailTexture();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetDetailName();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetDetailProperty();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCanShowDetail();
};
