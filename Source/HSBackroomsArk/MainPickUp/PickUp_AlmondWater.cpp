// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp_AlmondWater.h"

#include "Kismet/KismetSystemLibrary.h"

void APickUp_AlmondWater::OnUseFirst_Implementation(AMainCharacter* Character)
{
	Super::OnUseFirst_Implementation(Character);
	UKismetSystemLibrary::PrintString(GetWorld());
}
