// Fill out your copyright notice in the Description page of Project Settings.


#include "SteerPawn.h"

// Sets default values
ASteerPawn::ASteerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	steerComp = CreateDefaultSubobject<USteerComponent>("SteerComponent");
	AddOwnedComponent(steerComp);
	state = IDLE;

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

	switch (state)
	{
	case SEEK:
		SetActorLocation(steerComp->Seek(GetActorLocation(), target), false);
		break;
	case FLEE:
		SetActorLocation(steerComp->Flee(GetActorLocation(), target), false);
		break;
	case ARRIVAL:
		SetActorLocation(steerComp->Arrival(GetActorLocation(), slowing_d, target), false);
		break;
	case PURSUIT:
		SetActorLocation(steerComp->Pursuit(GetActorLocation(), follow_target->GetActorLocation(), follow_target->GetVelocity()), false);
		break;
	case EVASION:
		SetActorLocation(steerComp->Evasion(GetActorLocation(), follow_target->GetActorLocation(), follow_target->GetVelocity()), false);
		break;
	default:
		break;
	}

}

// Called to bind functionality to input
void ASteerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

void ASteerPawn::Seek(const FVector& pos) {
	state = SEEK;
	target = pos;
}

void ASteerPawn::Flee(const FVector& pos) {
	state = FLEE;
	target = pos;
}
void ASteerPawn::Arrival(const double slowing_dist, const FVector& pos) {
	state = ARRIVAL;
	target = pos;
	slowing_d = slowing_dist;
}

void ASteerPawn::Pursuit(APawn* follow) {
	state = PURSUIT;
	follow_target = follow;
}

void ASteerPawn::Evasion(APawn* follow) {
	state = EVASION;
	follow_target = follow;
}

inline FVector ASteerPawn::GetSteerVelocity() {
	return steerComp->GetVelocity();
}



