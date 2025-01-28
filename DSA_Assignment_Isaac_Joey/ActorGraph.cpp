#include "ActorGraph.h"
#include "Vector.h"
#include "AVLTree.h"
#include "Queue.h"

// add an actor to the graph 
ActorGraph::ActorGraph() {}

void ActorGraph::addActor(Actor* actor) {
	actorList.pushBack(actor);
	// create an empty vector of int (actor indices for related actors)
	adjacencyList.pushBack(Vector<int>());
}


// retrieve the index of the actor based on it's name 
int ActorGraph::searchIndex(string actorName) {
	for (int i = 0; i++; i < actorList.getLength()) {
		if (actorName == actorList[i]->getActorName()) {
			return i;
		}
	}
	return NULL;
}

// addRelationship (addEdges between nodes)
void ActorGraph::addRelation(string sourceActor, string destActor) {
	int sourceInd = searchIndex(sourceActor);
	int destInd = searchIndex(destActor);
	if (sourceInd || destInd == NULL) {
		return;
	}
	adjacencyList[sourceInd].pushBack(destInd);
	adjacencyList[destInd].pushBack(sourceInd);
}

// displayAllRelatedActors 
// Precondition: The graph (adjacencyList) must not be empty
// PostCondition: Display all neighbours of the source node until the second degree of seperation 
// Time complexity: O(n^2)
void ActorGraph::displayAllRelatedActors(string sourceActor) {
	// initialize vectors for tracking visited node,
	// initalize another vector for tracking each level in the graph 
	Vector<int> lvl;
	// initialize queue for processing all neighbours of the current node 
	Vector<bool> visited;
	Queue* neighbours = new Queue();
	
	// retrieve the index in adj list of sourceActor 
	int source = searchIndex(sourceActor);
	// mark source as vistied 
	visited[source] = true;
	lvl[source] = 0;

	// enqueue the source node 
	neighbours->enqueue(source);

	while (!neighbours->isEmpty()) {
		// dequeue the current node 
		int curr = 0;
		neighbours->getFront(curr);

		// print out the information of the actor 

		Actor* actorPtr = actorList[curr];
		actorPtr->displayInfo();
		neighbours->dequeue();

		if (lvl[curr] > 2) {
			break;
		}
		// process its neighbours 
		for (int i = 0; i < adjacencyList[curr].getLength(); i++) {
			if (!visited[i]) {
				visited[i] = true;
				lvl[i] = lvl[curr] + 1; // level of the current node add one 
				neighbours->enqueue(i);
			}
		}
	}
}
