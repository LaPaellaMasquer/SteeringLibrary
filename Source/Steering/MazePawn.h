// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SteerComponent.h"
#include "NodeGraph.h"
#include "MazePawn.generated.h"

UCLASS(Blueprintable)
class STEERING_API AMazePawn : public APawn
{
	GENERATED_BODY()
private:
	const double SWITCH_DISTANCE = 5;

	enum State { IDLE, PATH, CIRCUIT };
	State state;

	TArray<ANodeGraph*> circuit;
	int index;
	TArray<TArray<ANodeGraph*>> queue;

	TArray<ANodeGraph*> A_Star(ANodeGraph* start, ANodeGraph* goal);
	
public:
	UPROPERTY(EditAnywhere)
	USteerComponent* steerComp;

	UPROPERTY(EditAnywhere)
	ANodeGraph* graph;

	// Sets default values for this pawn's properties
	AMazePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveToNode(ANodeGraph* goal);

	UFUNCTION(BlueprintCallable)
	void CreateCircuit(ANodeGraph* goal);
};
