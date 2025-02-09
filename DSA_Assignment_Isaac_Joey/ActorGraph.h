// Team Member 1: Isaac Tiew Xun Yong (S10257760G) searhcIndex, displayAllRelatedActors, addActor
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
	/*
	* Precondition: the actorId provided in the arguments of the function must exists 
	* Postconsition: retrieves the corresponding index of the sourceActor
	* Time complexity: O(n) where n is the numbr of elements in the actorsList 
	*/
	int searchIndex(int sourceActorId);

	/*
	* Precondition: none 
	* Postcondition: The actor is added into the actorGraph, it has an empty adjacencyList for the corresponding actor in the graph
	* Time complexity: O(1) -> calls the pushBack method on the vector (this method increments the index to the last element in the vector to add a new one, insertion at rear O(1) 
	*/
	void addActor(Actor* actor);

	/*
	* Precondition: The sourceActorId and the destActorId given must exists within the actorGraph and actorList 
	* Postcondition: The destActorIndex is being added to the sourceActor's list of related actors (edges) the nested vector and vice versa 
	* Time Complexity: O(n) , insertion of destActor to sourceActor list of related actors and vice versa is an O(1) operation finding duplicate values 
	* checking if the destActorInd has already been added to the soureActor or the sourceActor has already been added to the destination actor is O(n), average time complexity is O(n)
	*/
	void addRelation(int sourceActorId, int destActorId);
	/*
	* Precondition: The sourceActorId must exist within the actorGraph 
	* Postcondition: All the actor's direct neighbours are displayed for indirect neighbours it is displayed up to two degree of seperation from the sourceActor
	* Time Complextty: O(V+E) where v is the number of vertices (actors) in the adjacencyList and E is the number of edges connections the source actor has 
	*/
	void displayAllRelatedActors(int sourceActorId);
	/*
	* Precondition: The adjacencyList must not be empty
	* Postcondition: All the objects in the adjacencyList are being displayed 
	* Time Complexity: O(n^2) as the algorithm retrieves each actor's neighbours in the adjacencyList, iterate thru all of its neighbours and display them
	*/
	void printAdjacencyList();
	/*
	* Precondition: The name of the actor must exist in the actorGraph 
	* Time complexity: O(n)
	*/
	int getActorByName(string name);

};

