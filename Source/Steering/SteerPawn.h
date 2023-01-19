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
	void Seek(const FVector& target);

	UFUNCTION(BlueprintCallable)
	void Flee(const FVector& target);

	UFUNCTION(BlueprintCallable)
	void Pursuit(const FVector& target, const FVector& velocity_target);

	UFUNCTION(BlueprintCallable)
	void Evasion( const FVector& target, const FVector& velocity_target);

	UFUNCTION(BlueprintCallable)
	void Arrival(const double slowing_d, const FVector& target);

	UFUNCTION(BlueprintCallable)
	inline FVector GetSteerVelocity();

};
