#pragma once 
#include "Vector.h"
#include "Actor.h"
#include "AVLTree.h"
class ActorGraph
{
private:
	Vector<Vector<int>> adjacencyList; // where the entire graph is stored 
	Vector<Actor*> actorList; // where each actor pointer is stored 
		// each actor corresponds to an index in adjacencyList 
public:
	ActorGraph();
	// addEdge() will add a the destination, the connected edges to the source 
	// and the source to the destination as well

	// A1 (Information) -> A2,A3,A5 pointers in a vector 
	// Take note that both source and destination are actually indices in the Graph

	// Search for index (Given an actor's name)
	// Loop through the outer vertex and return the index of the vertex element whose name matches 
	int searchIndex(int sourceActorId);
	void addActor(Actor*);
	void addRelation(int sourceActorId, int destActorId);
	void displayAllRelatedActors(int sourceActorId);
	void printAdjacencyList();
	int getActorByName(string name);


};

