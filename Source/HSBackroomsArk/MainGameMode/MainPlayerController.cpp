// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "MainCharacter.h"

AMainPlayerController::AMainPlayerController()
{
	
}

void AMainPlayerController::PawnLeavingGame()
{
	AMainCharacter* LeavePawn=Cast<AMainCharacter>(GetPawn());
	if (!LeavePawn)
	{
		GetPawn()->Destroy();
		SetPawn(NULL);
	}
	LeavePawn->OnPawnLeavingGame();
}
