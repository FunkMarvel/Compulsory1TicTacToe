// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameBoardPawn.generated.h"

UCLASS()
class COMPULSORY1TICTACTOE_API AGameBoardPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameBoardPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// My designated area
public:

	UFUNCTION(Category = "UFUNCTION")
		void SetColorOfSphere(int32 index, bool bPlayerOne);

	UFUNCTION(Category = "UFUNCTION")
		void ResetGameBoard();

	UFUNCTION()
		void DebugVoid();
	
	int DebugInt = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		float Spacing = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UStaticMeshComponent* StaticMeshComponent;

	// Array that keeps the 9 spheres
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyTools)
		TArray<UStaticMeshComponent*> SphereArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		TArray<int32> WhichPlayer;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		bool bPlayerTurn;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class USpringArmComponent* SpringArm;


	// Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UMaterial* BlueMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UMaterial* RedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UMaterial* WhiteMaterial;




};
