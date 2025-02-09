// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Main.generated.h"

class UUW_Bag;
class UUW_Detail;
class AMainCharacter;
class UScrollBox;

UCLASS()
class HSBACKROOMSARK_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	void FlushInteractList();

	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	UScrollBox* ScrollBox_InteractList;

	UPROPERTY(meta=(BindWidget))
	UUW_Bag* UMG_Bag_First;

	UPROPERTY(meta=(BindWidget))
	UUW_Bag* UMG_Bag_Second;

	UPROPERTY(meta=(BindWidget))
	UUW_Bag* UMG_Bag_Third;

	UPROPERTY(meta=(BindWidget))
	UUW_Bag* UMG_Bag_Fourth;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_Detail> DetailWidgetClass;
	
	AMainCharacter* Character;
	
};
