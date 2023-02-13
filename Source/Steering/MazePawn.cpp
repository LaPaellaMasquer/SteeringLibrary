// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePawn.h"

// Sets default values
AMazePawn::AMazePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	steerComp = CreateDefaultSubobject<USteerComponent>("SteerComponent");
	AddOwnedComponent(steerComp);
}

// Called when the game starts or when spawned
void AMazePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMazePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<ANodeGraph*> AMazePawn::A_Star(ANodeGraph* goal) {
	TArray<ANodeGraph*> nextNodes;
	nextNodes.add(graph);

	TMap<NodeGraph*, double> distances;
	distances[graph] = 0;

	TMap<NodeGraph*, NodeGraph*> path;
	TArray<ANodeGraph*> res;

	while (nextNodes.Num()!=0) {
		NodeGraph* current;
		// get the node with the minimum distances
		for (auto& e : distances) {
			current = e.Key;
			break;
		}

		if (current == goal) {
			res.add(current);
			for (NodeGraph* n : path) {
				res.Insert(n, 0);
			}
			return res;
		}

		nextNodes.Remmove(current);

		for (NodeGraph* n : current->Neighbours) {
			distance = distances[current] + (n->GetActorLocation() - current->GetActorLocation()).Length();
			if (!distances.Contains(n) || (distances.Contains(n) && distance < disances[n])) {
				distances[n] = distance
					path[n] = current;
			}
			distancesValueSort([](const double& A, const double& B) {
				return A < B;
			});
			nextNodes.addUUnique(n);
		}
	}
	return res;
}
