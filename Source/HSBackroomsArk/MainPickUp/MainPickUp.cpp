// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPickUp.h"

#include "Components/BoxComponent.h"
#include "HSBackroomsArk/MainGameMode/MainCharacter.h"
#include "HSBackroomsArk/MainGameMode/Widget/UW_Main.h"
#include "Kismet/KismetSystemLibrary.h"
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
	DOREPLIFETIME(AMainPickUp,CharacterList);
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
	}
}

void AMainPickUp::OnNotShowDetail_Implementation(AMainCharacter* Character)
{
	if (Character->IsLocallyControlled())
	{
		Character->DetailActorList.Remove(this);
		Character->MainWidget->FlushInteractList();
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
}

void AMainPickUp::OnNotInteract_Implementation(AMainCharacter* Character)
{
	Character->RunServer(this,2);
}

void AMainPickUp::OnRunServer_Implementation(AMainCharacter* Character,int Function)
{
	switch (Function)
	{
	case 1:
			UKismetSystemLibrary::PrintString(GetWorld(),"1");
			break;
		case 2:
			UKismetSystemLibrary::PrintString(GetWorld(),"2");
			break;
	}
}

void AMainPickUp::OnRunServerReliable_Implementation(AMainCharacter* Character, int Function)
{
	
}

void AMainPickUp::OnRep_CharacterList()
{
	
}
