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
	double max_speed;

public:	
	// Sets default values for this actor's properties
	ASteer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	FVector Seek(const FVector& position, FVector velocity, const FVector& target);

	FVector Flee(const FVector& position, FVector velocity, const FVector& target);

	FVector Arrival(const FVector& position, FVector velocity, const double slowing_d, const FVector& target);


};
