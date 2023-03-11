# MPIA Roussel Alan

## Installation
At the first time open the project Steering.uproject with Unreal Engine 5.0.3.
This will generate the Visual Studio project.
Open Steering.sln with Visual Studio Community 2022 to open the scripts to run and compile the project use Run Debug Windows Local.
The project contain 2 levels (in Map file), freefly and maze.

## Freefly Map
In this map you will control a simple cone which use steering principles.

Player pawn:
- Left Click on the ground -> seek to position 
- Left Click on other pawn -> pursuit 
- Shift + Left Click -> arrival 
- Right Click on the ground -> flee position
- Right Click on other pawn -> evasion

Circuit pawn:
- A -> circuit
- Z -> one way
- E -> two ways


## Maze Map
Move a pawn inside a maze with path planning.

Player Pawn:
- Left Click on node -> find a path to go to the selected node
- Right Click on node -> create a circuit which passes by the selected node and return to the current one

You could add node to the path or circuit when the pawn move.
But add node in path couldn't be made if a circuit is currently played and vice versa.

Camera movement:
W/A/S/D to move in all directions. 


