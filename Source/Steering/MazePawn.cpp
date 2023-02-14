// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePawn.h"

// Sets default values
AMazePawn::AMazePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	steerComp = CreateDefaultSubobject<USteerComponent>("SteerComponent");
	AddOwnedComponent(steerComp);

	state = IDLE;
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

	double d;
	switch (state)
	{
	case AMazePawn::IDLE:
		break;
	case AMazePawn::PATH:
		d = (circuit[index]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			graph = circuit[index];
			++index;
			if (index == circuit.Num()) {
				state = IDLE;
				circuit.Empty();
				index = 0;
				break;
			}
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), circuit[index]->GetActorLocation()), false);
		break;
	default:
		break;
	}

	if (state != IDLE) {
		FVector new_forward = steerComp->GetVelocity();
		new_forward.Normalize();
		SetActorRotation(new_forward.Rotation());
	}
}

// Called to bind functionality to input
void AMazePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<ANodeGraph*> AMazePawn::A_Star(ANodeGraph* goal) {
	TSet<ANodeGraph*> nextNodes;
	nextNodes.Add(graph);

	// distances form start to node n
	TMap<ANodeGraph*, double> distances;
	distances.Add(graph, 0);

	// heuristique distance from start to end by node n;
	TMap<ANodeGraph*, double> hdistances;
	hdistances.Add(graph, (goal->GetActorLocation() - graph->GetActorLocation()).Length());

	TMap<ANodeGraph*, ANodeGraph*> path;
	TArray<ANodeGraph*> res;
	while (!nextNodes.IsEmpty()) {
		ANodeGraph* current = nullptr;

		// get the node with the minimum heuristic distance
		double min = INFINITY;
		for (auto& n : nextNodes) {
			if (hdistances[n] < min) {
				current = n;
				min = hdistances[n];
			}
		}

		if (current == goal) {
			res.Add(current);
			while (path.Contains(current))
			{
				current = path[current];
				res.Insert(current, 0);
			}
			return res;
		}

		nextNodes.Remove(current);
		for (ANodeGraph* n : current->Neighbours) {
			double distance = distances[current] + (n->GetActorLocation() - current->GetActorLocation()).Length();
			bool isAlreadySaw = distances.Contains(n);

			if (!isAlreadySaw) {
				path.Add(n, current);
				distances.Add(n, distance);
				hdistances.Add(n, distance + (goal->GetActorLocation() - n->GetActorLocation()).Length());
				nextNodes.Add(n);
			}
			else if (distance < distances[n]) {
				path[n] = current;
				distances[n] = distance;
				hdistances[n] = distance + (goal->GetActorLocation() - n->GetActorLocation()).Length();
				nextNodes.Add(n);
			}
		}
	}
	return res;
}


void AMazePawn::MoveToNode(ANodeGraph* goal) {
	if (state == IDLE) {
		circuit = A_Star(goal);
		state = PATH;
		index = 0;
	}

	if (circuit.IsEmpty()) {
		state = IDLE;
	}
}