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

	TArray<ANodeGraph*> A_Star(ANodeGraph* goal);
	
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

	void MoveToNode(ANodeGraph* goal);
};
