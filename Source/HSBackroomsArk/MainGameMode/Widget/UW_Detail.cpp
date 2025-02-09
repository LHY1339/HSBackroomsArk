// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Detail.h"

#include "Components/Button.h"
#include "HSBackroomsArk/MainGameMode/MainCharacter.h"

void UUW_Detail::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Interact&&!__IsBind)
	{
		__IsBind=true;
		Button_Interact->OnPressed.AddDynamic(this,&UUW_Detail::Button_InteractPress);
	}
}

void UUW_Detail::Button_InteractPress()
{
	Character->Interact(DetailActor);
}
