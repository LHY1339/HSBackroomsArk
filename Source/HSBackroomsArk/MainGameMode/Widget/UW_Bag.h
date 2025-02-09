// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Bag.generated.h"

class UUW_Main;
class AMainCharacter;
class UImage;
class UButton;

UCLASS()
class HSBACKROOMSARK_API UUW_Bag : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Hold;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Icon;

	UPROPERTY(EditAnywhere)
	int32 BagIndex=0;

	UUW_Main* MainWidget;
};
