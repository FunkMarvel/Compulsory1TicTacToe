// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoardPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Containers/Array.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGameBoardPawn::AGameBoardPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	SphereArray.Init(NULL, 9);
	BoardState.Init(' ', 9);
	
	
	//gets the spghere meshes
	SphereArray[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere0MeshComponent"));
	SphereArray[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1MeshComponent"));
	SphereArray[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2MeshComponent"));
	SphereArray[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3MeshComponent"));
	SphereArray[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere4MeshComponent"));
	SphereArray[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere5MeshComponent"));
	SphereArray[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere6MeshComponent"));
	SphereArray[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere7MeshComponent"));
	SphereArray[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere9MeshComponent"));

	
	//Sets the Materials
	static ConstructorHelpers::FObjectFinder<UMaterial> BlueMat(TEXT("Material'/Game/Materials/BlueMaterial.BlueMaterial'"));
	BlueMaterial = BlueMat.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> RedMat(TEXT("Material'/Game/Materials/RedMaterial.RedMaterial'"));
	RedMaterial = RedMat.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> WhiteMat(TEXT("Material'/Game/Materials/WhiteMaterial.WhiteMaterial'"));
	WhiteMaterial = WhiteMat.Object;

	//spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->SetRelativeLocation(FVector::ZeroVector);
	SpringArm->TargetArmLength = 500.f;

	// camera setup
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	
	// hard coding way of getting the Sphere Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Game/Models/MaterialSphere.MaterialSphere'"));

	//sets the mesh and start Matierial for each sphere
	int ArraySize = SphereArray.Num();
	if (SphereMesh.Succeeded()) {
		for (int i = 0; i < ArraySize; i++) {
			SphereArray[i]->SetStaticMesh(SphereMesh.Object);
			SphereArray[i]->SetMaterial(0, WhiteMaterial);
			//SphereArray[i]->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

			//Set initial board state:
			BoardState[i] = '0' + i;
		}
	}
}

// Called when the game starts or when spawned
void AGameBoardPawn::BeginPlay()
{
	Super::BeginPlay();

	//Sets the Locations i do this in the BeginPlay to ensure location are correct
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			SphereArray[i * 3 + j]->SetRelativeLocation(FVector(Spacing * i - Spacing, Spacing * j - Spacing, 0.f));
		}
	}

	//sets the SpringArm location, to ensure correct location
	SpringArm->SetRelativeLocation(FVector::ZeroVector);
	UE_LOG(LogTemp, Warning, TEXT("Welcome! Player 1 press number of chosen sphere to begin."));
}

void AGameBoardPawn::OnPress1()
{
	int32 index{ 0 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress2()
{
	int32 index{ 1 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress3()
{
	int32 index{ 2 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress4()
{
	int32 index{ 3 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress5()
{
	int32 index{ 4 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress6()
{
	int32 index{ 5 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress7()
{
	int32 index{ 6 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress8()
{
	int32 index{ 7 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnPress9()
{
	int32 index{ 8 };
	OnAnyPress(index);
}

void AGameBoardPawn::OnAnyPress(int32 index)
{
	if (BoardState[index] != 'x' && BoardState[index] != 'o' && !bGameEnded) {

		UpdateBoardState(index);	// switch color and update game state
		bool bWin = CheckWin(BoardState);
		LastPos = index;

		if (bWin && bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 1 wins!\nPress 'Enter' to reset."));
			bGameEnded = true;
		}
		else if (bWin && !bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 2 wins!\nPress 'Enter' to reset."));
			bGameEnded = true;
		}
		else if (TurnCounter >= 9) {
			UE_LOG(LogTemp, Warning, TEXT("It's a draw!\nPress 'Enter' to reset."));
			bGameEnded = true;
		}
		bPlayerOne = !bPlayerOne;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Spot taken, try again."));
	}
	if (AIOn && !bPlayerOne && TurnCounter < 9)
	{
		UpdateBoardState(AISelection(0.f));
		bPlayerOne = !bPlayerOne;
	}
}

void AGameBoardPawn::UpdateBoardState(int32 index)
{
	//Updates internal game state and sphere materials.

	SetColorOfSphere(index);
	//UE_LOG(LogTemp, Warning, TEXT("DID FIND PAWN!!!!!!!!!\n\n\n"));

	if (bPlayerOne) {
		BoardState[index] = 'x';
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input: "));
	}
	else {
		BoardState[index] = 'o';
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input: "));
	}
	TurnCounter++;
}

bool AGameBoardPawn::CheckWin(TArray<TCHAR> &Board)
{
	//UE_LOG(LogTemp, Warning, TEXT("Checking for win"));
	// Function that checks entire board and returns a bool of value true
	// if a win has been reached and value false if no win has been reached.

	bool bWin{ false };  // return value.

	// looping through BoardState:
	for (int i = 0; i < BoardWidth; i++)
	{
		// checking row number i for win and returns true if true:
		bWin = (Board[i * BoardWidth] == Board[i * BoardWidth + 1] && Board[i * BoardWidth] == Board[i * BoardWidth + 2]);
		if (bWin) return bWin;

		// checking column number i for win and returns true if true:
		bWin = (Board[i] == Board[i + BoardWidth] && Board[i] == Board[i + 2 * BoardWidth]);
		if (bWin) return bWin;
	}

	// checks upper-left to lower-right diagonal for win and returns true if true:
	bWin = (Board[0] == Board[BoardWidth + 1] && Board[0] == Board[2 * BoardWidth + 2]);
	if (bWin) return bWin;

	// checks lower-left to upper-right diagonal for win and returns true if true:
	bWin = (Board[2] == Board[BoardWidth + 1] && Board[2] == Board[2 * BoardWidth]);

	return bWin;  // returns false if end of function is reached. 
}

int32 AGameBoardPawn::AISelection()
{
	// Function making ai selection. Returns integer corresponding to selected square.
	// Args:
	//	&Board - TArray of TCHARs passed by refrence,
	//			 containing the squares of the board.
	//	weight - float between 0 and 1 corresponding to selected difficulty.

	int32 Selection{};  // return variable.

	// creates copy of current game board state:
	TArray<TCHAR> TestBoard = BoardState;

	// variables for storing indices that can be selected:
	TArray<int32> PossibleSelections;
	int32 PossibleWin{ -1 };  // stores index of winning move.
	int32 PossibleLoss{ -1 };  // stores index of losing move.
	bool MiddleFree{ false };  // stores state of middle square.


	// looping through table:
	for (int i = 0; i < BoardWidth * BoardWidth; i++)
	{
		// finds empty squares:
		if (TestBoard[i] != 'x' && TestBoard[i] != 'o') {

			// checks if current square can lead to win if selected:
			TestBoard[i] = 'o';
			if (CheckWin(TestBoard)) PossibleWin = i;  // stores index of winning selection.

			// checks if current square can lead to loss if not selected:
			TestBoard[i] = 'x';
			if (CheckWin(TestBoard)) PossibleLoss = i;  // stores index of possible loss.

			if (i == 4) { MiddleFree = true; } // checks if middle is free.
			else { PossibleSelections.Add(i); }  // stores index of square if free and not middle.
			TestBoard[i] = BoardState[i];  // resets value of current square to match the current state of the game.
		}
	}

	// creates random number genenrator for ai behaviour:
	// Draws a random real number between 0 and 1 to compare with difficulty weight:
	float Percent = FMath::RandRange(0.f, 1.f); // A lower weight makes the ai more likely to play correct moves, and thus increases the difficulty.
	int32 RandIndex = FMath::RandRange(0, PossibleSelections.Num() - 1);  // int distrobution for random selection.


	if (Percent > weight && PossibleWin >= 0) {
		// possible win is selected if random number is bigger than the difficulty weight:
		Selection = PossibleWin;
	}
	else if (Percent > weight && PossibleLoss >= 0) {
		// possible loss is prevented if random number is bigger than the difficulty weight:
		Selection = PossibleLoss;
	}
	else if (MiddleFree) {
		// middle is selected if it is free:
		Selection = 4;
	}
	else {
		// if no other selection has been made, then a random free square is chosen:
		Selection = PossibleSelections[RandIndex];
	}

	return Selection;  // returns number of selected square.
}

// Called every frame
void AGameBoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//lerp the locations of sphere every frame
	SetSphereLocations();

}

// Called to bind functionality to input
void AGameBoardPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent != nullptr)
	{
		// pick sphere actions:
		PlayerInputComponent->BindAction("PressOne", IE_Pressed, this, &AGameBoardPawn::OnPress1);
		PlayerInputComponent->BindAction("PressTwo", IE_Pressed, this, &AGameBoardPawn::OnPress2);
		PlayerInputComponent->BindAction("PressThree", IE_Pressed, this, &AGameBoardPawn::OnPress3);
		PlayerInputComponent->BindAction("PressFour", IE_Pressed, this, &AGameBoardPawn::OnPress4);
		PlayerInputComponent->BindAction("PressFive", IE_Pressed, this, &AGameBoardPawn::OnPress5);
		PlayerInputComponent->BindAction("PressSix", IE_Pressed, this, &AGameBoardPawn::OnPress6);
		PlayerInputComponent->BindAction("PressSeven", IE_Pressed, this, &AGameBoardPawn::OnPress7);
		PlayerInputComponent->BindAction("PressEight", IE_Pressed, this, &AGameBoardPawn::OnPress8);
		PlayerInputComponent->BindAction("PressNine", IE_Pressed, this, &AGameBoardPawn::OnPress9);

		//reset game action:
		PlayerInputComponent->BindAction("PressEnterReset", IE_Pressed, this, &AGameBoardPawn::ResetGameBoard);
	}
}

void AGameBoardPawn::SetColorOfSphere(int32 index)
{
	//if out of range, return with error code
	if (index < 0 || index > SphereArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("%s SetColorOfSphere got an index higher than the sphere array size."), *GetOwner()->GetName());
		return;
	}

	//change color based of active player
	if (bPlayerOne) {
		SphereArray[index]->SetMaterial(0, BlueMaterial);
	}
	else {
		SphereArray[index]->SetMaterial(0, RedMaterial);
	}

	return;
}

void AGameBoardPawn::ResetGameBoard()
{
	for (int32 i = 0; i < SphereArray.Num(); i++)
	{
		SphereArray[i]->SetMaterial(0, WhiteMaterial);

		//Set initial board state:
		BoardState[i] = '0' + i;
	}
	TurnCounter = 0;
	bPlayerOne = true;
	bGameEnded = false;
	LastPos = -1;
	return;
}

void AGameBoardPawn::SetSphereLocations(){
	
	for (int i = 0; i < SphereArray.Num(); i++) {
		if (i == LastPos) {
			// gets the location of sphere
			FVector Location = SphereArray[i]->GetRelativeLocation();
			// to the height axis, lerp to main actor pos + height
			Location.Z = FMath::FInterpTo(Location.Z, GetActorLocation().Z + Height, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f);
			SphereArray[i]->SetRelativeLocation(Location);
		}	
		else {
			//gets the location of sphere
			FVector Location = SphereArray[i]->GetRelativeLocation();
			// to the height axis, lerp to main actor pos
			Location.Z = FMath::FInterpTo(Location.Z, GetActorLocation().Z, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f);
			SphereArray[i]->SetRelativeLocation(Location);
		}
	}
}



