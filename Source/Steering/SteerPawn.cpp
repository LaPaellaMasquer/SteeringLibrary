// Fill out your copyright notice in the Description page of Project Settings.


#include "SteerPawn.h"

// Sets default values
ASteerPawn::ASteerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	steerComp = CreateDefaultSubobject<USteerComponent>("SteerComponent");
	AddOwnedComponent(steerComp);

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

void ASteerPawn::Seek(const FVector& target) {
	SetActorLocation(steerComp->Seek(GetActorLocation(), target), false);
}

void ASteerPawn::Flee(const FVector& target) {
	SetActorLocation(steerComp->Flee(GetActorLocation(), target), false);
}

void ASteerPawn::Pursuit(const FVector& target, const FVector& velocity_target) {
	SetActorLocation(steerComp->Pursuit(GetActorLocation(), target, velocity_target), false);
}

void ASteerPawn::Evasion(const FVector& target, const FVector& velocity_target) {
	SetActorLocation(steerComp->Evasion(GetActorLocation(), target, velocity_target), false);
}

void ASteerPawn::Arrival(const double slowing_d, const FVector& target) {
	SetActorLocation(steerComp->Arrival(GetActorLocation(), slowing_d, target), false);
}

inline FVector ASteerPawn::GetSteerVelocity() {
	return steerComp->GetVelocity();
}



