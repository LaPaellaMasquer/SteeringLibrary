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
	enum State {IDLE, SEEK, FLEE, ARRIVAL, PURSUIT, EVASION, LOOP, FORWARD, BACKWARD, PATH};
	const double SWITCH_DISTANCE = 1;

	State state;
	float slowing_d;
	FVector target;
	APawn* follow_target;
	int curr_checkpoint;
	int index_order;

public:
	UPROPERTY(EditAnywhere)
	USteerComponent *steerComp;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> checkpoints;

	UPROPERTY(EditAnywhere)
	TArray<int> order;

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
	void Arrival(const FVector& pos);

	UFUNCTION(BlueprintCallable)
	void Pursuit(APawn* follow);

	UFUNCTION(BlueprintCallable)
	void Evasion(APawn* follow);

	UFUNCTION(BlueprintCallable)
	void Circuit();

	UFUNCTION(BlueprintCallable)
	void OneWay();

	UFUNCTION(BlueprintCallable)
	void TwoWay();

	virtual FVector GetVelocity() const override;

	UFUNCTION(BlueprintCallable)
	float GetMass() const;

	UFUNCTION(BlueprintCallable)
	void SetMass(float m) ;

	UFUNCTION(BlueprintCallable)
	float GetForce() const;

	UFUNCTION(BlueprintCallable)
	void SetForce(float f) ;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable)
	void SetSpeed(float s) ;

	UFUNCTION(BlueprintCallable)
	float GetSlowingDistance() const;

	UFUNCTION(BlueprintCallable)
	void SetSlowingDistance(float d);
};
