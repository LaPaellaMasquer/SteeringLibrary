// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Steer.generated.h"

UCLASS()
class STEERING_API ASteer : public AActor
{
	GENERATED_BODY()
	
private:
	float mass;
	FVector position;
	FVector velocity;
	FMatrix orientation;
	float max_force;
	float max_speed;

	FVector Truncate(const FVector& v, double m) {
		return (m * v) / v.Length();
	}

public:	
	// Sets default values for this actor's properties
	ASteer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	FVector Seek(const FVector& position, const FVector& target);

	FVector Flee(const FVector& position, const FVector& target);

	FVector Pursuit(const FVector& position, const FVector& target, const FVector& velocity_target);

	FVector Evasion(const FVector& position, const FVector& target, const FVector& velocity_target);

	FVector Arrival(const FVector& position, const double slowing_d, const FVector& target);


};
