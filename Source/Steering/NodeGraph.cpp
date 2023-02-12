// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeGraph.h"

// Sets default values
ANodeGraph::ANodeGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANodeGraph::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ANodeGraph*> ANodeGraph::GetNeighbours(){
	return Neighbours;
}

