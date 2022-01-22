// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBoardPawn.h"

#include "GetPawnTestActor.h"

// Sets default values for this component's properties
UGetPawnTestActor::UGetPawnTestActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGetPawnTestActor::BeginPlay()
{
	Super::BeginPlay();

	GameBoard = (AGameBoardPawn*)GetOwner();
	// ...
	if (GameBoard != nullptr)
	{
		//GameBoard->GetAllSpheres()[3]->SetRelativeLocation(FVector(10.f,0.f, 145.f));
		UE_LOG(LogTemp, Warning, TEXT("DID FIND PAWN!!!!!!!!!\n\n\n"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s"));
	}

}


// Called every frame
void UGetPawnTestActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

