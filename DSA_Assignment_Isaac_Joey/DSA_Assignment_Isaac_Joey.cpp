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
#include <iomanip>  // For setw
#include "AVLTree.h"
#include <ctime>
using namespace std;
void displayMenu();
void displayUserMenu();
void displayAdminMenu();
void displaySelectUser();
void addRelationship(HashTable<Actor>* actors, HashTable<Movie>* movies);
void handleUserFunctions(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph);
void addKnownActorsFromCast(ActorGraph* actors, HashTable<Movie>* movieHash); 
int partition(Vector<Movie*> movies, int left, int right);
void sortMovies(Vector<Movie*> movies, int left, int right);
int partitionActors(Vector<Actor*> actors, int left, int right);
void sortActors(Vector<Actor*> actors, int left, int right);


int main() {
	Vector<int> numbers;
	numbers.pushBack(1);
	numbers.pushBack(2);
	HashTable<Movie>* movieHashTable = new HashTable<Movie>();
	HashTable<Actor>* actorHashTable = new HashTable<Actor>();
	ActorGraph* actorGraph = new ActorGraph();

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

		/*cout << "This is the actor's name: " << actorName << endl;*/

		int aid = stoi(actorId);
		int actorBirthYear = stoi(actorBYear);
		Actor actor(aid,actorName,actorBirthYear);
		//actor.displayInfo();
		actorHashTable->add(actorBirthYear, actor);
		// find the actor 
		AVLNode<Actor>* actorNode = actorHashTable->search(aid);
		Actor* actorPtr = &(actorNode->item);
		actorGraph->addActor(actorPtr);

	}

	actorStream.close();
	actorGraph->displayAllActors();
	actorGraph->searchIndex(641);
	int index;
	index = actorGraph->searchIndex(641);
	cout << "This is actor's 641: " << index << endl;
	// Insert the relationship between the actors and the movies 
	addRelationship(actorHashTable, movieHashTable);

	// Insert known actors into the graph 
	addKnownActorsFromCast(actorGraph, movieHashTable);

	actorGraph->displayAllRelatedActors(102);

	cout << "Welcome to the movie database" << endl;
	while (true) {
		displaySelectUser();
		cout << endl;
		int useOption;
		cin >> useOption;
		if (useOption = 1) {
			handleUserFunctions(actorHashTable,movieHashTable,actorGraph);
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

// Precondition: The actor HashTable is not null, and the cast csv is also not empty 
// Postcondition: Add all known actors to a graph called actorGraph based on the given condition stated in the requirements both actors stared in the same movie or an actor knows another actor through a middleman (actor A2)
// Time Complexity: TBD
// For each actor maintain a list of vectors that will add actors belonging to the same movie 


void addKnownActorsFromCast(ActorGraph* actors, HashTable<Movie>* movieHash) {
	ifstream castStream("cast.csv");
	if (castStream.is_open()) {
		string castLine;
		getline(castStream, castLine);  // Read headers

		while (getline(castStream, castLine)) {
			stringstream cs(castLine);
			string PId, mID;
			getline(cs, PId, ','); // Read person id
			getline(cs, mID, ','); // Read movie id

			int movieId = stoi(mID); // Convert movieId to integer

			// Search for the movie in the movieHash
			AVLNode<Movie>* movieNode = movieHash->search(movieId);
			if (movieNode != nullptr) {
				// Retrieve the actors who starred in the same movie
				Vector<Actor*> cast = movieNode->relatedPointers;
				if (cast.getLength() > 0) {
					for (int i = 0; i < cast.getLength(); i++) {
						for (int j = i + 1; j < cast.getLength(); j++) {  // j starts from i + 1 to avoid double counting
							Actor* currActor = cast[i];
							Actor* nextActor = cast[j];
							cout << "Adding " << currActor->getActorName() << " with " << nextActor->getActorName() << endl;
							actors->addRelation(currActor->getKey(), nextActor->getKey());
						}
					}
				}
			}
			else {
				cout << "Error retrieving movie node for movieId: " << movieId << endl;
			}
		}
		castStream.close();
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
	cout << "[0] to exit" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void handleUserFunctions(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph) {
	while (true) {
		displayUserMenu();
		cout << endl;
		int option;
		cout << "Enter the option to choose" << endl;
		cin >> option;

		if (option == 1) {
			cout << "Enter the age range of the actor in the following format (youngestAge - oldestage): ";
			string range;
			string yAge;
			string oldAge;
			cin.ignore();
			getline(cin, range);
			// split the string 
			stringstream ss(range);
			getline(ss, yAge, ' '); // split just before the space 
			ss.ignore();
			getline(ss, oldAge);

			int youngestAge = stoi(yAge);
			int oldestAge = stoi(oldAge);

			int olderBirthYear = 2025 - oldestAge;
			int youngerBirthYear = 2025 - youngestAge;
			cout << left << setw(10) << "Actor Id"
				<< left << setw(25) << "Actor Name"
				<< left << setw(10) << "Actor Birth Year"
				<< endl;
			for (int i = olderBirthYear; i <= youngerBirthYear; i++) {
				// call the getKey function 
				AVLTree<Actor>* avlTreePtr = actorhash->getKey(i);
				// print the items 
				if (avlTreePtr->getRoot() != nullptr) {
					avlTreePtr->print();
				}
			}
		}
		else if (option == 2) {

			time_t t = time(0);  // Get current time
			struct tm now;       // Create a tm structure
			localtime_s(&now, &t); // Use localtime_s (safe version)

			int currentYear = now.tm_year + 1900;  // Get the current year 
			int lowYear = currentYear - 3;
			for (int i = lowYear; i <= currentYear; i++) {
				cout << i << endl;
				AVLTree<Movie>* avlMoviePtr = movieHash->getKey(i);
			}

		}

		else if (option == 3) {
			// retrieve all actors first 
			cout << "Enter the actorId of the specific actor: ";
			int actorId;
			cin >> actorId;
			AVLNode<Actor>* actorAVL = actorhash->search(actorId);
			if (actorAVL != nullptr) {
				Vector<Movie*> movies;
				movies = actorAVL->relatedPointers;
				sortMovies(movies,0,movies.getLength()-1);

				// display in sorted order 
				if (movies.getLength() > 0) {
					cout << left << setw(10) << "Movie Id"
						 << left << setw(25) << "Movie Title"
						 << left << setw(10) << "Year Released"
						 << endl;
					for (int i = 0; i < movies.getLength(); i++) {
						movies[i]->displayInfo();
					}
				}
			}
		}

		else if (option == 4) {
			// retrieve all movies first 
			cout << "Enter the movieId of the specific movie: ";
			int movieId;
			cin >> movieId;
			cout << movieId << endl;
			AVLNode<Movie>* movieAVL = movieHash->search(movieId);
			if (movieAVL != nullptr) {
				Vector<Actor*> cast;
				cast = movieAVL->relatedPointers;
				sortActors(cast,0,cast.getLength()-1);
				if (cast.getLength() > 0) {
					cout << left << setw(10) << "Actor Id"
						 << left << setw(25) << "Actor Name"
						 << left << setw(10) << "Actor Birth Year"
						 << endl;
					for (int i = 0; i < cast.getLength(); i++) {
						Actor* a = cast[i];
						a->displayInfo();
					}
				}
				
			}
		}
		
		else if (option == 0) {
			break;
		}
	}

}

int partition(Vector<Movie*> movies, int left, int right) {
	Movie* pivot = movies[(left + right) / 2];
	while (left < right) {
		while (movies[left]->getMovieTitle() < pivot->getMovieTitle()) {
			left++; // increase the left index 
		}
		while (movies[right]->getMovieTitle() > pivot->getMovieTitle()) {
			right--;
		}
		if (left < right) {
			Movie* temp = movies[left];
			movies[left] = movies[right];
			movies[right] = temp;
		}

		
	}
	return left; // left is the new pivot
}

// quickSort implementation to sort the movies
void sortMovies(Vector<Movie*> movies, int left, int right) {
	int q = partition(movies, left, right);
	if (left < right) {
		sortMovies(movies, left, q-1); // left
		sortMovies(movies, q+1,right); // right
	}
	else {
		return;
	}
}
// quickSort implementation for actors (thing is triggered here)
int partitionActors(Vector<Actor*> actors, int left, int right) {
	Actor* pivot = actors[(left + right) / 2];
	while (left <= right) {
		while (actors[left]->getActorName() < pivot->getActorName()) {
			cout << "Sorting" << actors[left]->getActorName() <<  " and " << pivot->getActorName() << endl;
			left++; // increase the left index 
		}
		while (actors[right]->getActorName() > pivot->getActorName()) {
			right--;
		}
		if (left <= right) {
			Actor* temp = actors[left];
			actors[left] = actors[right];
			actors[right] = temp;
			left++;
			right--;
		}


	}
	return left; // left is the new pivot
}

// quickSort implementation to sort the movies
void sortActors(Vector<Actor*> actors, int left, int right) {
	if (left < right) {
		int q = partitionActors(actors, left, right);
		sortActors(actors, left, q - 1); // left
		sortActors(actors, q+1, right); // right
	}
	else {
		return;
	}
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
