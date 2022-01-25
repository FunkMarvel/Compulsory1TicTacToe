// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "GameLogicComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMPULSORY1TICTACTOE_API UGameLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameLogicComponent();
	// setup input
	// setup gameboard
	
	// on keypress iterate game state according to input
	// track number of turns
	// evaluate game over conditions
	// take new input
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// handles input:
	void SetupInput(UInputComponent* PlayerInputComponent);

	// functions called on keypress:
	void OnPress1();
	void OnPress2();
	void OnPress3();
	void OnPress4();
	void OnPress5();
	void OnPress6();
	void OnPress7();
	void OnPress8();
	void OnPress9();

	void UpdateBoardState(int32 index);
	bool CheckWin();
	
	UInputComponent* PlayerInputComponent;

	class AGameBoardPawn* GameBoard = nullptr;
	TArray<TCHAR> BoardState;
	int32 BoardWidth;
	
	bool bPlayerOne;
	int32 TurnCounter;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
