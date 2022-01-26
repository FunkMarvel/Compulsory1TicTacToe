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

	void OnAnyPress(int32 index);

	void UpdateBoardState(int32 index);
	bool CheckWin(TArray<TCHAR>& Board);

	int32 AISelection();

	TArray<TCHAR> BoardState;
	int32 BoardWidth = 3;

	bool bPlayerOne = true;
	bool bGameEnded = false;
	int32 TurnCounter;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintImplementableEvent)
		void ReturnToMenu();

	// My designated area
public:
	int32 LastPos = -1;
	
	UFUNCTION(Category = "UFUNCTION")
		void SetSphereLocations();

	UFUNCTION(Category = "UFUNCTION")
		void SetColorOfSphere(int32 index);

	UFUNCTION(Category = "UFUNCTION")
		void ResetGameBoard();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		float Spacing = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		float Height = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		class UStaticMeshComponent* StaticMeshComponent;

	// Array that keeps the 9 spheres
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		TArray<UStaticMeshComponent*> SphereArray;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		bool AIOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTools")
		float AIWeight = 0.5;
};
