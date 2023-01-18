// Fill out your copyright notice in the Description page of Project Settings.


#include "SteerComponent.h"

// Sets default values for this component's properties
USteerComponent::USteerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USteerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void USteerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

FVector USteerComponent::Truncate(FVector v, float m) {
	return (m * v) / v.Length();
}

FVector USteerComponent::Seek(const FVector& position, const FVector& target) {
	FVector res = target - position;
	res.Normalize();
	res -= velocity;

	return res;
}

FVector USteerComponent::Flee(const FVector& position, const FVector& target) {
	FVector res = (target - position) * -1;
	res.Normalize();
	res -= velocity;

	return res;
}


FVector USteerComponent::Pursuit(const FVector& position, const FVector& target, const FVector& velocity_target) {
	FVector d = target - position;
	FVector unit_forward = velocity;
	unit_forward.Normalize();
	FVector unit_forward_target = velocity_target;
	unit_forward_target.Normalize();
	double t = FVector::DotProduct(unit_forward, unit_forward_target) * FVector::DotProduct(velocity_target, d);

	return Seek(position, target + velocity_target * t);
}

FVector USteerComponent::Evasion(const FVector& position, const FVector& target, const FVector& velocity_target) {
	FVector d = target - position;
	FVector unit_forward = velocity;
	unit_forward.Normalize();
	FVector unit_forward_target = velocity_target;
	unit_forward_target.Normalize();
	double t = FVector::DotProduct(unit_forward, unit_forward_target) * FVector::DotProduct(velocity_target, d);

	return Flee(position, target + velocity_target * t);
}

FVector USteerComponent::Arrival(const FVector& position, const double slowing_d, const FVector& target) {
	FVector res = target - position;
	double d = res.Length();
	double ramped_speed = max_speed * (d / slowing_d);
	res *= FMath::Min(ramped_speed, max_speed) / d;
	res -= velocity;

	return res;
}

inline FVector USteerComponent::GetVelocity(){
	return velocity;
}

FVector USteerComponent::Compute(FVector pos, FVector steering) {
	FVector acceleration =  Truncate(steering, max_force) / mass;
	velocity = Truncate(velocity + acceleration, max_speed);

	return pos + velocity;
}