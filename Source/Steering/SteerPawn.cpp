// Fill out your copyright notice in the Description page of Project Settings.


#include "SteerPawn.h"

// Sets default values
ASteerPawn::ASteerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASteerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASteerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}



