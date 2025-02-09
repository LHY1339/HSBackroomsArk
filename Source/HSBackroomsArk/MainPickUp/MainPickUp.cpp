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
		SM_Third->SetRenderCustomDepth(true);
		Character->DetailActorList.Add(this);
		Character->MainWidget->FlushInteractList();
		CharacterList.Add(Character);
	}
}

void AMainPickUp::OnNotShowDetail_Implementation(AMainCharacter* Character)
{
	if (Character->IsLocallyControlled())
	{
		SM_Third->SetRenderCustomDepth(false);
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
	Interact(Character);
}

void AMainPickUp::OnRunServer_Implementation(AMainCharacter* Character,int Function)
{
	
}

void AMainPickUp::OnRunServerReliable_Implementation(AMainCharacter* Character, int Function)
{
	
}

bool AMainPickUp::GetCanInteract_Implementation()
{
	return CanPickUp;
}

void AMainPickUp::OnHold_Implementation(AMainCharacter* Character)
{
	if (!Character->HoldAsset)
	{
		Hold(Character);
		return;
	}
	IIHold* Interface=Cast<IIHold>(Character->HoldAsset);
	if (!Interface)
	{
		Hold(Character);
		return;
	}
	if (Character->HoldAsset==this)
	{
		Interface->Execute_OnNotHold(Character->HoldAsset,Character);
		return;
	}
	Interface->Execute_OnNotHold(Character->HoldAsset,Character);
	Hold(Character);
}

void AMainPickUp::OnNotHold_Implementation(AMainCharacter* Character)
{
	NotHold(Character);
}

void AMainPickUp::OnUseFirst_Implementation(AMainCharacter* Character)
{

}

void AMainPickUp::OnUseSecond_Implementation(AMainCharacter* Character)
{

}

void AMainPickUp::OnDrop_Implementation(AMainCharacter* Character)
{
	Drop(Character);
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

void AMainPickUp::Interact(AMainCharacter* Character)
{
	if (!CanPickUp)
	{
		return;
	}
	for (int32 i=0;i<Character->BagList.Num();i++)
	{
		if (!Character->BagList[i])
		{
			SetOwner(Character);
			CanPickUp=false;
			AttachToComponent(Character->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SM_First->SetVisibility(false);
			SM_Third->SetVisibility(false);
			Character->BagList[i]=this;
			break;
		}
	}
	if (Character->IsLocallyControlled())
	{
		Character->MainWidget->FlushInteractList();
	}
}

void AMainPickUp::Hold(AMainCharacter* Character)
{
	SM_First->AttachToComponent(Character->SK_First,FAttachmentTransformRules::SnapToTargetNotIncludingScale,AttachSocketName);
	SM_Third->AttachToComponent(Character->SK_Third,FAttachmentTransformRules::SnapToTargetNotIncludingScale,AttachSocketName);
	SM_First->SetVisibility(true);
	SM_Third->SetVisibility(true);
	Character->HoldAsset=this;
}

void AMainPickUp::NotHold(AMainCharacter* Character)
{
	SM_First->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SM_Third->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SM_First->SetVisibility(false);
	SM_Third->SetVisibility(false);
	Character->HoldAsset=nullptr;
}

void AMainPickUp::Drop(AMainCharacter* Character)
{
	SetOwner(nullptr);
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative,true));
	SM_First->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SM_Third->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SM_First->SetVisibility(true);
	SM_Third->SetVisibility(true);
	Character->BagList[Character->BagList.Find(this)]=nullptr;
	CanPickUp=true;
	if (Character->IsLocallyControlled())
	{
		Character->MainWidget->FlushInteractList();
	}
}
