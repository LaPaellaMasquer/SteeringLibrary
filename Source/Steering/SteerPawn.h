// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SteerComponent.h"
#include "SteerPawn.generated.h"

UCLASS(Blueprintable)
class STEERING_API ASteerPawn : public APawn
{
	GENERATED_BODY()

private:
	enum State {IDLE, SEEK, FLEE, ARRIVAL, PURSUIT, EVASION, LOOP, ROUND};
	State state; 
	FVector target;
	FVector velocity_target;
	float slowing_d;
	APawn* follow_target;

public:
	UPROPERTY(EditAnywhere)
	USteerComponent *steerComp;

	// Sets default values for this pawn's properties
	ASteerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Seek(const FVector& pos);

	UFUNCTION(BlueprintCallable)
	void Flee(const FVector& pos);

	UFUNCTION(BlueprintCallable)
	void Arrival(const double slowing_d, const FVector& pos);

	UFUNCTION(BlueprintCallable)
	void Pursuit(APawn* follow);

	UFUNCTION(BlueprintCallable)
	void Evasion(APawn* follow);

	UFUNCTION(BlueprintCallable)
	inline FVector GetSteerVelocity();

};
