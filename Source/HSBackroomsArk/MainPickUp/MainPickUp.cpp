// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPickUp.h"

#include "Components/BoxComponent.h"
#include "HSBackroomsArk/MainGameMode/MainCharacter.h"
#include "HSBackroomsArk/MainGameMode/Widget/UW_Main.h"
#include "Net/UnrealNetwork.h"

AMainPickUp::AMainPickUp()
{
	BOX_Collision=CreateDefaultSubobject<UBoxComponent>("BOX_Collision");
	SetRootComponent(BOX_Collision);

	SM_Third=CreateDefaultSubobject<UStaticMeshComponent>("SM_Third");
	SM_Third->SetupAttachment(RootComponent);

	SM_First=CreateDefaultSubobject<UStaticMeshComponent>("SM_First");
	SM_First->SetupAttachment(RootComponent);
}

void AMainPickUp::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainPickUp,CanPickUp);
}

void AMainPickUp::OnView_Implementation(AMainCharacter* Character)
{
	Character->ViewActorList.Add(this);
}

void AMainPickUp::OnNotView_Implementation(AMainCharacter* Character)
{
	Character->ViewActorList.Remove(this);
}

UTexture2D* AMainPickUp::GetViewTexture_Implementation()
{
	return ViewTexture;
}

FVector2D AMainPickUp::GetViewTextureSize_Implementation()
{
	return ViewTextureSize;
}

FVector AMainPickUp::GetViewOffset_Implementation()
{
	return ViewOffset;
}

bool AMainPickUp::GetCanView_Implementation()
{
	return CanPickUp;
}

void AMainPickUp::OnShowDetail_Implementation(AMainCharacter* Character)
{
	if (Character->IsLocallyControlled())
	{
		Character->DetailActorList.Add(this);
		Character->MainWidget->FlushInteractList();
		CharacterList.Add(Character);
	}
}

void AMainPickUp::OnNotShowDetail_Implementation(AMainCharacter* Character)
{
	if (Character->IsLocallyControlled())
	{
		Character->DetailActorList.Remove(this);
		Character->MainWidget->FlushInteractList();
		CharacterList.Add(Character);
	}
}

UTexture2D* AMainPickUp::GetDetailTexture_Implementation()
{
	return DetailTexture;
}

FString AMainPickUp::GetDetailName_Implementation()
{
	return DetailName;
}

FString AMainPickUp::GetDetailProperty_Implementation()
{
	return DetailProperty;
}

bool AMainPickUp::GetCanShowDetail_Implementation()
{
	return CanPickUp;
}

void AMainPickUp::OnInteract_Implementation(AMainCharacter* Character)
{
	Character->RunServer(this,1);
	Character->MainWidget->FlushInteractList();
}

void AMainPickUp::OnNotInteract_Implementation(AMainCharacter* Character)
{
	
}

void AMainPickUp::OnRunServer_Implementation(AMainCharacter* Character,int Function)
{
	switch (Function)
	{
	case 1:
		PickUp(Character);
		break;
	case 2:
		Drop(Character);
		break;
	}
}

void AMainPickUp::OnRunServerReliable_Implementation(AMainCharacter* Character, int Function)
{
	
}

bool AMainPickUp::GetCanInteract_Implementation()
{
	return CanPickUp;
}

void AMainPickUp::OnRep_CanPickUp()
{
	for (int32 i=0;i<CharacterList.Num();i++)
	{
		if (CharacterList[i]->IsLocallyControlled())
		{
			CharacterList[i]->MainWidget->FlushInteractList();
		}
	}
}

void AMainPickUp::PickUp(AMainCharacter* Character)
{
	if (!CanPickUp)
	{
		return;
	}
	CanPickUp=false;
	AttachToComponent(Character->GetRootComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SM_First->SetVisibility(false);
	SM_Third->SetVisibility(false);
}

void AMainPickUp::Drop(AMainCharacter* Character)
{
	
}
