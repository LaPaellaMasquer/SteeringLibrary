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
	curr_checkpoint = -1;
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
	double d;
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *steerComp->GetVelocity().ToString()));
		break;
	case PURSUIT:
		SetActorLocation(steerComp->Pursuit(GetActorLocation(), follow_target->GetActorLocation(), follow_target->GetVelocity()), false);
		break;
	case EVASION:
		SetActorLocation(steerComp->Evasion(GetActorLocation(), follow_target->GetActorLocation(), follow_target->GetVelocity()), false);
		break;
	case LOOP:
		d = (checkpoints[curr_checkpoint]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			++index_order;
			if (index_order == order.Num()) {
				index_order = 0;
			}
			curr_checkpoint = order[index_order];
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), checkpoints[curr_checkpoint]->GetActorLocation()), false);
		break;
	case FORWARD:
		d = (checkpoints[curr_checkpoint]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			++index_order;
			if (index_order == order.Num()) {
				index_order -= 2;
				state = BACKWARD;
			}
			curr_checkpoint = order[index_order];
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), checkpoints[curr_checkpoint]->GetActorLocation()), false);
		break;
	case BACKWARD:
		d = (checkpoints[curr_checkpoint]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			--index_order;
			if (index_order == -1) {
				index_order += 2;
				state = FORWARD;
			}
			curr_checkpoint = order[index_order];
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), checkpoints[curr_checkpoint]->GetActorLocation()), false);
		break;
	case PATH:
		d = (checkpoints[curr_checkpoint]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			++index_order;
			if (index_order == order.Num()) {
				--index_order;
				state = IDLE;
				break;
			}
			curr_checkpoint = order[index_order];
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), checkpoints[curr_checkpoint]->GetActorLocation()), false);
		break;
	default:
		break;
	}

	if (state != IDLE && steerComp->GetVelocity() != FVector::ZeroVector) {
		FVector new_forward = steerComp->GetVelocity();
		new_forward.Normalize();
		FVector new_side = FVector::CrossProduct(new_forward, GetActorUpVector());
		FVector new_up = FVector::CrossProduct(new_forward, new_side);

		SetActorRotation(new_forward.Rotation());
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

void ASteerPawn::Circuit() {
	state = LOOP;
	if (curr_checkpoint == -1) {
		curr_checkpoint = order[0];
		index_order = 0;
	}
}

void ASteerPawn::OneWay() {
	state = PATH;
	if (curr_checkpoint == -1) {
		curr_checkpoint = order[0];
		index_order = 0;
	}
}

void ASteerPawn::TwoWay() {
	state = FORWARD;
	if (curr_checkpoint == -1) {
		curr_checkpoint = order[0];
		index_order = 0;
	}
}

FVector ASteerPawn::GetVelocity() const {
	return steerComp->GetVelocity();
}



