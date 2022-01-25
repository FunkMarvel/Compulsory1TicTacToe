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


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	
	//gets the Sphere Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Game/Models/MaterialSphere.MaterialSphere'"));

	//sets the mesh and start Matierial
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
	UE_LOG(LogTemp, Warning, TEXT("PRESSU DESUUUUU!"));
	if (BoardState[index] != 'x' && BoardState[index] != 'o') {
		UE_LOG(LogTemp, Warning, TEXT("ACCEPTED PRESS!"));
		UpdateBoardState(index);	// switch color and update game state
		bool win = CheckWin();
		LastPos = index;

		if (win && bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 1 wins!"));
		}
		else if (win && !bPlayerOne) {
			UE_LOG(LogTemp, Warning, TEXT("Player 2 wins!"));
		}
		else if (TurnCounter >= 9) {
			UE_LOG(LogTemp, Warning, TEXT("It's a draw!"));
		}
		bPlayerOne = !bPlayerOne;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Spot taken, try again."));
	}
}

void AGameBoardPawn::UpdateBoardState(int32 index)
{
	//Updates internal game state and sphere materials.

	SetColorOfSphere(index);
	UE_LOG(LogTemp, Warning, TEXT("DID FIND PAWN!!!!!!!!!\n\n\n"));

	if (bPlayerOne) {
		BoardState[index] = 'x';
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input: "));
	}
	else {
		BoardState[index] = 'o';
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input: "));
	}
	TurnCounter++;
}

bool AGameBoardPawn::CheckWin()
{
	UE_LOG(LogTemp, Warning, TEXT("Checking for win"));
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

// Called every frame
void AGameBoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSphereLocations();

}

// Called to bind functionality to input
void AGameBoardPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAction("PressOne", IE_Pressed, this, &AGameBoardPawn::OnPress1);
		PlayerInputComponent->BindAction("PressTwo", IE_Pressed, this, &AGameBoardPawn::OnPress2);
		PlayerInputComponent->BindAction("PressThree", IE_Pressed, this, &AGameBoardPawn::OnPress3);
		PlayerInputComponent->BindAction("PressFour", IE_Pressed, this, &AGameBoardPawn::OnPress4);
		PlayerInputComponent->BindAction("PressFive", IE_Pressed, this, &AGameBoardPawn::OnPress5);
		PlayerInputComponent->BindAction("PressSix", IE_Pressed, this, &AGameBoardPawn::OnPress6);
		PlayerInputComponent->BindAction("PressSeven", IE_Pressed, this, &AGameBoardPawn::OnPress7);
		PlayerInputComponent->BindAction("PressEight", IE_Pressed, this, &AGameBoardPawn::OnPress8);
		PlayerInputComponent->BindAction("PressNine", IE_Pressed, this, &AGameBoardPawn::OnPress9);
	}
}

void AGameBoardPawn::SetColorOfSphere(int32 index)
{
	if (index < 0 || index > SphereArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("%s SetColorOfSphere got an index higher than the sphere array size."), *GetOwner()->GetName());
		return;
	}


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
	return;
}

void AGameBoardPawn::SetSphereLocations(){
	
	for (int i = 0; i < SphereArray.Num(); i++) {
		if (i == LastPos) {
			FVector Location = SphereArray[i]->GetRelativeLocation();
			Location.Z = FMath::FInterpTo(Location.Z, GetActorLocation().Z + Height, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f);
			SphereArray[i]->SetRelativeLocation(Location);
		}	
		else {
			FVector Location = SphereArray[i]->GetRelativeLocation();
			Location.Z = FMath::FInterpTo(Location.Z, GetActorLocation().Z, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f);
			SphereArray[i]->SetRelativeLocation(Location);
		}
	}
}



