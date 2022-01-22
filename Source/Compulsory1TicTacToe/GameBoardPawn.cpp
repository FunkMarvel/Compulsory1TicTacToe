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
	bPlayerTurn = false;

	//SphereArray[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1MeshComponent"));
	SphereArray[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere0MeshComponent"));
	SphereArray[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1MeshComponent"));
	SphereArray[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2MeshComponent"));
	SphereArray[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3MeshComponent"));
	SphereArray[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere4MeshComponent"));
	SphereArray[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere5MeshComponent"));
	SphereArray[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere6MeshComponent"));
	SphereArray[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere7MeshComponent"));
	SphereArray[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere9MeshComponent"));


	//materials
	BlueMaterial = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	RedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	WhiteMaterial = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));


	//spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	// 
	static ConstructorHelpers::FObjectFinder<UMaterial> TestMat(TEXT("Material'/Game/Materials/WhiteMaterial.WhiteMaterial'"));

	int ArraySize = WhichPlayer.Num();
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Game/Models/MaterialSphere.MaterialSphere'"));


	if (SphereMesh.Succeeded()) {
		for (int i = 0; i < ArraySize; i++) {
			SphereArray[i]->SetStaticMesh(SphereMesh.Object);
			SphereArray[i]->SetMaterial(0, TestMat.Object);
			//SphereArray[i]->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

		}
	}


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			SphereArray[i * 3 + j]->SetWorldLocation(FVector(100.f * i, 100.f * j, 0.f));
		}
	}
}

// Called when the game starts or when spawned
void AGameBoardPawn::BeginPlay()
{
	Super::BeginPlay();



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

TArray<UStaticMeshComponent*> AGameBoardPawn::GetAllSpheres()
{
	return SphereArray;
}

void AGameBoardPawn::OnPressed1() {

	
}
void AGameBoardPawn::OnPressed2() {


}

void AGameBoardPawn::OnPressed3() {


}

void AGameBoardPawn::OnPressed4() {


}
void AGameBoardPawn::OnPressed5() {


}
void AGameBoardPawn::OnPressed6() {


}
void AGameBoardPawn::OnPressed7() {


}
void AGameBoardPawn::OnPressed8() {


}
void AGameBoardPawn::OnPressed9() {


}

