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
	if (state != IDLE) {

		if (circuit.IsEmpty() && !queue.IsEmpty()) {
			circuit = queue[0];
			queue.RemoveAt(0);
			index = 0;
		}
		else if (circuit.IsEmpty() && queue.IsEmpty()) {
			state = IDLE;
			return;
		}

		d = (circuit[index]->GetActorLocation() - GetActorLocation()).Length();
		if (d <= SWITCH_DISTANCE) {
			graph = circuit[index];
			++index;
			if (index == circuit.Num()) {
				circuit.Empty();
				return;
			}
		}
		SetActorLocation(steerComp->Seek(GetActorLocation(), circuit[index]->GetActorLocation()), false);
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

TArray<ANodeGraph*> AMazePawn::A_Star(ANodeGraph* start, ANodeGraph* goal) {
	TSet<ANodeGraph*> nextNodes;
	nextNodes.Add(start);

	// distances form start to node n
	TMap<ANodeGraph*, double> distances;
	distances.Add(start, 0);

	// heuristique distance from start to end by node n;
	TMap<ANodeGraph*, double> hdistances;
	hdistances.Add(start, (goal->GetActorLocation() - start->GetActorLocation()).Length());

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
	if (!queue.IsEmpty()) {
		queue.Add(A_Star(queue.Last().Last(), goal));
	}
	else if(!circuit.IsEmpty())
	{
		queue.Add(A_Star(circuit.Last(), goal));
	}
	else {
		queue.Add(A_Star(graph, goal));
		state = PATH;
	}
}

void AMazePawn::CreateCircuit(ANodeGraph* goal)
{
	if (state == PATH) {
		return;
	}

	if (!queue.IsEmpty()) {
		ANodeGraph* start = queue.Last().Last();
		if (queue.Num() != 1) {
			queue.Add(A_Star(queue.Last(1).Last(), goal));
		}
		else {
			queue.Add(A_Star(circuit.Last(), goal));
		}
		queue.Add(A_Star(goal, start));
		queue.RemoveAt(queue.Num()-3);
	}
	else if (!circuit.IsEmpty())
	{
		ANodeGraph* start = circuit.Last();
		queue.Add(A_Star(start, goal));
		queue.Add(A_Star(goal, start));
	}
	else {
		queue.Add(A_Star(graph, goal));
		queue.Add(A_Star(goal, graph));
		state = CIRCUIT;
	}
}
