// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSBackroomsArk/Interface/IDetail.h"
#include "HSBackroomsArk/Interface/IHold.h"
#include "HSBackroomsArk/Interface/IInteract.h"
#include "HSBackroomsArk/Interface/IRPC.h"
#include "HSBackroomsArk/Interface/IView.h"
#include "MainPickUp.generated.h"

class UBoxComponent;
class AMainCharacter;

UCLASS()
class HSBACKROOMSARK_API AMainPickUp : public AActor,public IIView,public IIDetail,public IIInteract,public IIRPC,public IIHold
{
	GENERATED_BODY()

public:
	AMainPickUp();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	//Interface
	virtual void OnView_Implementation(AMainCharacter* Character) override;
	virtual void OnNotView_Implementation(AMainCharacter* Character) override;
	virtual UTexture2D* GetViewTexture_Implementation() override;
	virtual FVector2D GetViewTextureSize_Implementation() override;
	virtual FVector GetViewOffset_Implementation() override;
	virtual bool GetCanView_Implementation() override;

	virtual void OnShowDetail_Implementation(AMainCharacter* Character) override;
	virtual void OnNotShowDetail_Implementation(AMainCharacter* Character) override;
	virtual UTexture2D* GetDetailTexture_Implementation() override;
	virtual FString GetDetailName_Implementation() override;
	virtual FString GetDetailProperty_Implementation() override;
	virtual bool GetCanShowDetail_Implementation() override;

	virtual void OnInteract_Implementation(AMainCharacter* Character) override;
	virtual bool GetCanInteract_Implementation() override;

	virtual void OnRunServer_Implementation(AMainCharacter* Character,int Function) override;
	virtual void OnRunServerReliable_Implementation(AMainCharacter* Character, int Function) override;

	virtual void OnHold_Implementation(AMainCharacter* Character) override;
	virtual void OnNotHold_Implementation(AMainCharacter* Character) override;
	virtual void OnUseFirst_Implementation(AMainCharacter* Character) override;
	virtual void OnUseSecond_Implementation(AMainCharacter* Character) override;
	virtual void OnDrop_Implementation(AMainCharacter* Character) override;

public:
	//UFUNCTION
	UFUNCTION()
	void OnRep_CanPickUp();

	void Interact(AMainCharacter* Character);
	void Hold(AMainCharacter* Character);
	void NotHold(AMainCharacter* Character);
	void Drop(AMainCharacter* Character);
	
public:
	//Defaults
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BOX_Collision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SM_First;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SM_Third;

	//Variable
	UPROPERTY(EditAnywhere,Category="View")
	UTexture2D* ViewTexture;

	UPROPERTY(EditAnywhere,Category="View")
	FVector2D ViewTextureSize;

	UPROPERTY(EditAnywhere,Category="View")
	FVector ViewOffset;

	UPROPERTY(EditAnywhere,Category="Detail")
	UTexture2D* DetailTexture;

	UPROPERTY(EditAnywhere,Category="Detail")
	FString DetailName;

	UPROPERTY(EditAnywhere,Category="Detail")
	FString DetailProperty;

	UPROPERTY(EditAnywhere)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_CanPickUp)
	bool CanPickUp=true;
	
	TArray<AMainCharacter*> CharacterList;
};


