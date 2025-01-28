// DSA_Assignment_Isaac_Joey.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Actor.h"
#include "Movie.h"
#include "Vector.h"
#include "ActorGraph.h"
#include "HashTable.h"
#include "AVLTree.h"
using namespace std;
void displayMenu();
void displayUserMenu();
void displayAdminMenu();
void displaySelectUser();
void addRelationship(HashTable<Actor>* actors, HashTable<Movie>* movies);

int main() {

	HashTable<Movie>* movieHashTable = new HashTable<Movie>();
	HashTable<Actor>* actorHashTable = new HashTable<Actor>();

	ifstream movieStream("movies.csv");
	ifstream actorStream("actors.csv");

	// Check if the file is open
	if (!movieStream.is_open()) {
		cerr << "Could not open the file!" << endl;
		return 1;
	}

	string line;
	// Skip the header line
	getline(movieStream, line);  // Read and discard the header
	getline(actorStream, line);
	// Read data lines
	while (getline(movieStream, line)) {
		stringstream ss(line);
		string movId, movName, movTitle, movPlot, movYear;

		// Extract each field of the movie seperated by the comma delimeter 
		getline(ss, movId, ',');   // Movie ID
		getline(ss, movTitle, ','); // Movie Name
		getline(ss, movPlot, ','); // Release Year
		getline(ss, movYear, ',');

		int movieId = stoi(movId);
		int movRYear = stoi(movYear);

		Movie movie(movieId, movTitle, movPlot, movRYear);
		// add movie to hashTable 
		movieHashTable->add(movRYear, movie);

		cout << "Movie Title: " << movTitle << endl;
	}

	movieStream.close();
	// line would be each line of the excel file 
	while (getline(actorStream, line)) {
		stringstream sa(line);
		// Extract each field inside the actor file 
		string actorId, actorName, actorBYear;
		getline(sa, actorId, ',');
		getline(sa, actorName, ',');
		getline(sa, actorBYear, ',');

		cout << "This is the actor's name: " << actorName << endl;

		int aid = stoi(actorId);
		int actorBirthYear = stoi(actorBYear);
		Actor actor(aid,actorName,actorBirthYear);
		actor.displayInfo();
		actorHashTable->add(actorBirthYear, actor);

	}

	actorStream.close();

	// Insert the relationship between the actors and the movies 
	addRelationship(actorHashTable, movieHashTable);
}

// Precondition: There must be an actor that is existing within the hash table 
// Postcondition: The movie is added to the corresponding actor node based on their cast csv, the actor is added to the movie node based on cast csv 
void addRelationship(HashTable<Actor>* actors, HashTable<Movie>* movies) {
	// read the cast csv 
	ifstream castStream("cast.csv");
	if (castStream.is_open() != NULL) {
		string line;
		getline(castStream, line);
		while (getline(castStream, line)) {
			stringstream cs(line);
			string pId, mId;
			getline(cs, pId, ',');
			getline(cs, mId, ',');
			int actorId = stoi(pId);
			int movieId = stoi(mId);
			// add movie to actor 
			AVLNode<Movie>* movieNode = movies->search(movieId);
			AVLNode<Actor>* actorNode = actors->search(actorId);
			movieNode->item.displayInfo();
			actorNode->item.displayInfo();
			cout << endl;
			Movie* moviePtr = &(movieNode->item);
			moviePtr->displayInfo();
			Actor*  actorPtr = &(actorNode->item);

			// push_back the movie to the actor
			movieNode->relatedPointers.pushBack(actorPtr);
			actorNode->relatedPointers.pushBack(moviePtr);
		}
		castStream.close();

	}

	else {
		cout << "The file given is not opened";
	}

	
}
void displayMenu() {
	cout << "Welcome to the movie database" << endl;
	
	while (true) {
		displaySelectUser();
		cout << endl;
		int useOption;
		cin >> useOption;
		if (useOption = 1) {
			// handle user functions 
			displayUserMenu();
			break;
		}

		else if (useOption = 2) {
			cout << "Admin selected " << endl;
			break;
		}
		else {
			break;
		}
	}


}

void displaySelectUser() {
	cout << "--------- Select a User ---------" << endl;
	cout << "[1] User" << endl;
	cout << "[2] Admin" << endl;
	cout << "[0] Exit" << endl;
	cout << "---------------------------------" << endl;
}

void displayAdminMenu() {
	cout << "--------- Select an admin feature ---------" << endl;
	cout << "[1] Add new actor" << endl;
	cout << "[2] Add new movie" << endl;
	cout << "[3] add an actor to a movie" << endl;
	cout << "[4] Update actor/movie details" << endl;
	cout << "---------------------------------" << endl;
}

void displayUserMenu() {
	cout << "----------------------------- Select a user feature ------------------------------" << endl;
	cout << "[1] Display (in ascending order of age) the actors with age between x and y (inclusive)" << endl;
	cout << "[2] Display movies made within the past 3 years (in ascending order of year)" << endl;
	cout << "[3] Display all movies an actor starred in (in alphabetical order)" << endl;
	cout << "[4] Display all the actors in a particular movie (in alphabetical order)" << endl;
	cout << "[5] Display a list of all actors that a particular actor knows." << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
