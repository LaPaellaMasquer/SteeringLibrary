// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeGraph.generated.h"

UCLASS(Blueprintable)
class STEERING_API ANodeGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)

	TArray<ANodeGraph*> Neighbours;

	// Sets default values for this actor's properties
	ANodeGraph();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<ANodeGraph*> GetNeighbours();
};
