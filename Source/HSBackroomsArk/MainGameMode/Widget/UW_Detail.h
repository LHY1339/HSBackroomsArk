// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Detail.generated.h"

class AMainCharacter;
class UButton;
class IIDetail;
/**
 * 
 */
UCLASS()
class HSBACKROOMSARK_API UUW_Detail : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void Button_InteractPress();

	UFUNCTION()
	void Button_InteractRelease();

	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Interact;
	
	AActor* DetailActor;
	AMainCharacter* Character;

private:
	bool __IsBind=false;
};
