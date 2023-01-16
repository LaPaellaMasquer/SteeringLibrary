// Fill out your copyright notice in the Description page of Project Settings.


#include "Steer.h"

// Sets default values
ASteer::ASteer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASteer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ASteer::Seek(const FVector& position, const FVector& target) {
	FVector res = target - position;
	res.Normalize();
	res -= velocity;

	return res;
}

FVector ASteer::Flee(const FVector& position, const FVector& target) {
	FVector res = (target - position) * -1;
	res.Normalize();
	res -= velocity;

	return res;
}


FVector ASteer::Pursuit(const FVector& position, const FVector& target, const FVector& velocity_target) {
	FVector d = target - position;
	FVector unit_forward = velocity;
	unit_forward.Normalize();
	FVector unit_forward_target = velocity_target;
	unit_forward_target.Normalize();
	double t = FVector::DotProduct(unit_forward, unit_forward_target) * FVector::DotProduct(velocity_target, d);
	
	return Seek(position, target + velocity_target * t);
}

FVector ASteer::Evasion(const FVector& position, const FVector& target, const FVector& velocity_target) {
	FVector d = target - position;
	FVector unit_forward = velocity;
	unit_forward.Normalize();
	FVector unit_forward_target = velocity_target;
	unit_forward_target.Normalize();
	double t = FVector::DotProduct(unit_forward, unit_forward_target) * FVector::DotProduct(velocity_target, d);

	return Flee(position, target + velocity_target * t);
}

FVector ASteer::Arrival(const FVector& position, const double slowing_d, const FVector& target) {
	FVector res = target - position;
	double d = res.Length();
	double ramped_speed = max_speed * (d / slowing_d);
	res *= FMath::Min(ramped_speed, max_speed) / d;
	res -= velocity;

	return res;
}

