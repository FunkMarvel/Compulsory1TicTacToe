// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

AGamePlayerController::AGamePlayerController() {
}

void AGamePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent()->BindAction("PickSphere", IE_Pressed, this, &AGamePlayerController::UpdateBoard);
}