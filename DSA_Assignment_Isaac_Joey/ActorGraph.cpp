#include "ActorGraph.h"
#include "Vector.h"
#include "AVLTree.h"
#include "Queue.h"

// add an actor to the graph 
ActorGraph::ActorGraph() {}

void ActorGraph::addActor(Actor* actor) {
	actor->displayInfo();
	actorList.pushBack(actor);
	// create an empty vector of int (actor indices for related actors)
	adjacencyList.pushBack(Vector<int>());
}


void ActorGraph::displayAllActors() {
	for (int i = 0; i < actorList.getLength(); i++) {
		Actor a = *(actorList[i]);
		cout << i  << endl;
		a.displayInfo();
	}
}


// retrieve the index of the actor based on it's name 
int ActorGraph::searchIndex(int actorId) {
	cout << actorId << endl;
	for (int i = 0; i < actorList.getLength(); i++) {
		Actor a = *(actorList[i]);
		if (actorId == a.getKey()) {
			cout << a.getKey() << endl;
			return i;
		}
	}
	return NULL;
}

// addRelationship (addEdges between nodes)
void ActorGraph::addRelation(int sourceActorId, int destinationActorId) {
	// Get the indices of both actors in the actor list
	int sourceInd = searchIndex(sourceActorId);
	int destInd = searchIndex(destinationActorId);

	// If either index is invalid (e.g., -1 or NULL), do nothing
	if (sourceInd == -1 || destInd == -1) {
		return;  // Either actor was not found
	}

	// Print the indices for debugging
	cout << sourceInd << endl;
	cout << destInd << endl;

	// Prevent adding duplicate relationships by checking if the connection already exists
	Vector<int>& sourceAdjList = adjacencyList[sourceInd];
	Vector<int>& destAdjList = adjacencyList[destInd];

	// Add the relationship if it's not already present (Prevent duplicate adding)
	bool sourceExists = false;
	for (int i = 0; i < sourceAdjList.getLength(); ++i) {
		if (sourceAdjList[i] == destInd) {
			sourceExists = true;
			break;
		}
	}

	bool destExists = false;
	for (int i = 0; i < destAdjList.getLength(); ++i) {
		if (destAdjList[i] == sourceInd) {
			destExists = true;
			break;
		}
	}

	if (!sourceExists) {
		sourceAdjList.pushBack(destInd);
	}

	if (!destExists) {
		destAdjList.pushBack(sourceInd);
	}
}



// displayAllRelatedActors 
// Precondition: The graph (adjacencyList) must not be empty
// PostCondition: Display all neighbours of the source node until the second degree of seperation 
// Time complexity: O(n^2)
void ActorGraph::displayAllRelatedActors(int sourceActorId) {
	// initialize vectors for tracking visited node,
	// initalize another vector for tracking each level in the graph 
	Vector<int> lvl;
	// initialize queue for processing all neighbours of the current node 
	Vector<bool> visited;
	Queue* neighbours = new Queue();
	
	// retrieve the index in adj list of sourceActor 
	int source = searchIndex(sourceActorId);
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


void ActorGraph::printAdjacencyList() {
	// Check if the actorList and adjacencyList are valid
	if (actorList.getLength() == 0) {
		std::cout << "No actors in the list." << std::endl;
		return;
	}

	// Loop through each actor in the actorList
	for (int i = 0; i < actorList.getLength(); ++i) {
		Actor* actor = actorList[i];

		// Print the actor's name and key (or other relevant info)
		std::cout << "Actor " << actor->getActorName() << " (" << actor->getKey() << "): ";

		// Get the corresponding adjacency list for this actor
		Vector<int> adjList = adjacencyList[i];

		// If the actor has no connections, print "No connections"
		if (adjList.getLength() == 0) {
			std::cout << "No connections" << std::endl;
		}
		else {
			// Otherwise, print the indices of the connected actors
			for (int j = 0; j < adjList.getLength(); ++j) {
				// Print the index of the connected actor
				int connectedActorIndex = adjList[j];
				std::cout << connectedActorIndex << " ";  // Print index instead of actor name
			}
			std::cout << std::endl;
		}
	}
}



