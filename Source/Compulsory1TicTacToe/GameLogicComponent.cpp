// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogicComponent.h"

// Sets default values for this component's properties
UGameLogicComponent::UGameLogicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UGameLogicComponent::SetupInput()
{
	PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress1);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress2);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress3);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress4);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress5);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress6);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress7);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress8);
		PlayerInputComponent->BindAction("MyAction", IE_Pressed, this, &OnPress9);
	}
}

void UGameLogicComponent::OnPress1()
{
	// check availability
	// switch color and update game state
	// perform win check
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

