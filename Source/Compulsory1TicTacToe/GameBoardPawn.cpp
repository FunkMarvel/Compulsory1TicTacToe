// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Containers/Array.h"
#include "Components/StaticMeshComponent.h"

#include "GameBoardPawn.h"

// Sets default values
AGameBoardPawn::AGameBoardPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	SphereArray.Init(NULL, 9);
	WhichPlayer.Init(0, 9);
	


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
	SpringArm->TargetArmLength = 400.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	
	//gets the Sphere Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Game/Models/MaterialSphere.MaterialSphere'"));

	//sets the mesh and start Matierial
	int ArraySize = WhichPlayer.Num();
	if (SphereMesh.Succeeded()) {
		for (int i = 0; i < ArraySize; i++) {
			SphereArray[i]->SetStaticMesh(SphereMesh.Object);
			SphereArray[i]->SetMaterial(0, WhiteMaterial);
			//SphereArray[i]->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

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
}

// Called every frame
void AGameBoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameBoardPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);




}

void AGameBoardPawn::SetColorOfSphere(int32 index, bool bPlayerOne)
{
	if (index < 0 || index > SphereArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("%s SetColorOfSphere got an index higher than the sphere array size."), *GetOwner()->GetName());
		return;
	}


	if (bPlayerOne)
	{
		SphereArray[index]->SetMaterial(0, BlueMaterial);
	}
	else
	{
		SphereArray[index]->SetMaterial(0, RedMaterial);
	}

	return;
}

void AGameBoardPawn::ResetGameBoard()
{
	for (int32 i = 0; i < SphereArray.Num(); i++)
	{
		SphereArray[i]->SetMaterial(0, WhiteMaterial);
	}
	return;
}

