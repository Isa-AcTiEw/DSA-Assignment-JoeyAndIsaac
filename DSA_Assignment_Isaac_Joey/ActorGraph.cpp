#include "ActorGraph.h"
#include "Vector.h"
#include "AVLTree.h"
#include "Queue.h"

// add an actor to the graph 
ActorGraph::ActorGraph() {}

void ActorGraph::addActor(Actor* actor) {
	//actor->displayInfo();
	actorList.pushBack(actor);
	// create an empty vector of int (actor indices for related actors)
	adjacencyList.pushBack(Vector<int>());
}



// retrieve the index of the actor based on it's name 
int ActorGraph::searchIndex(int actorId) {
	for (int i = 0; i < actorList.getLength(); i++) {
		Actor a = *(actorList[i]);
		if (actorId == a.getKey()) {
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
	//cout << sourceInd << endl;
	//cout << destInd << endl;

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
	// initialize vectors for tracking visited node with size of adjacencyList and a default value
	// initalize another vector for tracking each level in the graph with size of adjacencyList and a default value
	int length = adjacencyList.getLength();
	Vector<int> lvl(adjacencyList.getLength(),-1); 
	// initialize queue for processing all neighbours of the current node 
	Vector<bool> visited(adjacencyList.getLength(),false);
	// intialize all visited to false
	Queue* neighbours = new Queue();
	// mark source as vistied 
	visited[sourceActorId] = true;
	lvl[sourceActorId] = 0;
	neighbours->enqueue(sourceActorId);

	while (!neighbours->isEmpty()) {
		// dequeue the current node 
		int curr;
		neighbours->getFront(curr);
		// print out the information of the actor 

		Actor* actorPtr = actorList[curr];
		neighbours->dequeue();

		if (lvl[curr] != 0) {
			actorPtr->displayInfo();
		}

		if (lvl[curr] == 2) {
			break;
		}
		// init a new vertex to access the all the related nodes of the actors
		Vector<int> temp = adjacencyList[curr];
		for (int i = 0; i < temp.getLength(); i++) {
			// check if the node have been visited 
			int actorIndex = temp[i];
			if (visited[actorIndex] == false) {
				visited[actorIndex] = true;
				Actor* neighActor = actorList[actorIndex];
				neighbours->enqueue(actorIndex);
				lvl[actorIndex] = lvl[curr] + 1;
			}
			else {
				continue;
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
		//std::cout << "Actor " << actor->getName() << " (" << actor->getKey() << "): ";

		// Get the corresponding adjacency list for this actor
		Vector<int> adjList = adjacencyList[i];

		// If the actor has no connections, print "No connections"
		if (adjList.getLength() == 0) {
		}
		else {
			// Otherwise, print the indices of the connected actors
			for (int j = 0; j < adjList.getLength(); ++j) {
				// Print the index of the connected actor
				int connectedActorIndex = adjList[j];
			}
		}
	}
}

int ActorGraph::getActorByName(string name) {
	for (int i = 0; i < actorList.getLength(); i++) {
		if (actorList[i]->getName() == name) {
			return i;
		}
	}
}



