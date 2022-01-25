// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBoardPawn.h"
#include "GameLogicComponent.h"

// Sets default values for this component's properties
UGameLogicComponent::UGameLogicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bPlayerOne = true;
	TurnCounter = 0;
	BoardWidth = 3;

	BoardState.Init(' ', 9);

	GameBoard = (AGameBoardPawn*)GetOwner();

	// ...
}


void UGameLogicComponent::SetupInput(UInputComponent* PlayerInputComponent)
{

	if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress1);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress2);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress3);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress4);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress5);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress6);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress7);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress8);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &UGameLogicComponent::OnPress9);
	}
}

void UGameLogicComponent::OnPress1()
{
	int32 index{ 0 };

	if (BoardState[index] == ' ') {
		UpdateBoardState(index);	// switch color and update game state
		if (CheckWin() && bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 1 wins!"));
		}
		else if (CheckWin() && !bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 2 wins!"));
		}
	}
}

void UGameLogicComponent::OnPress2()
{
}

void UGameLogicComponent::OnPress3()
{
}

void UGameLogicComponent::OnPress4()
{
}

void UGameLogicComponent::OnPress5()
{
}

void UGameLogicComponent::OnPress6()
{
}

void UGameLogicComponent::OnPress7()
{
}

void UGameLogicComponent::OnPress8()
{
}

void UGameLogicComponent::OnPress9()
{
}

bool UGameLogicComponent::CheckWin()
{
	// Function that checks entire board and returns a bool of value true
	// if a win has been reached and value false if no win has been reached.

	bool win{ false };  // return value.

	// looping through BoardState:
	for (int i = 0; i < BoardWidth; i++)
	{
		// checking row number i for win and returns true if true:
		win = (BoardState[i * BoardWidth] == BoardState[i * BoardWidth + 1] && BoardState[i * BoardWidth] == BoardState[i * BoardWidth + 2]);
		if (win) return win;

		// checking column number i for win and returns true if true:
		win = (BoardState[i] == BoardState[i + BoardWidth] && BoardState[i] == BoardState[i + 2 * BoardWidth]);
		if (win) return win;
	}

	// checks upper-left to lower-right diagonal for win and returns true if true:
	win = (BoardState[0] == BoardState[BoardWidth + 1] && BoardState[0] == BoardState[2 * BoardWidth + 2]);
	if (win) return win;

	// checks lower-left to upper-right diagonal for win and returns true if true:
	win = (BoardState[2] == BoardState[BoardWidth + 1] && BoardState[2] == BoardState[2 * BoardWidth]);
	if (win) return win;

	return win;  // returns false if end of function is reached. 
}

void UGameLogicComponent::UpdateBoardState(int32 index)
{
	//GameBoard = (AGameBoardPawn*)GetOwner();
	// ...
	if (GameBoard != nullptr)
	{
		GameBoard->SetColorOfSphere(index, bPlayerOne);
		UE_LOG(LogTemp, Warning, TEXT("DID FIND PAWN!!!!!!!!!\n\n\n"));

		if (bPlayerOne) { 
			BoardState[index] = 'x';
			UE_LOG(LogTemp, Warning, TEXT("Player 1 input: "));
		}
		else {
			BoardState[index] = 'o';
			UE_LOG(LogTemp, Warning, TEXT("Player 2 input: "));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s"));
	}

}

// Called when the game starts
void UGameLogicComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameLogicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

