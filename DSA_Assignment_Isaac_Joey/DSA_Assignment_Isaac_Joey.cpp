// DSA_Assignment_Isaac_Joey.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Team Member 1: Isaac Tiew Xun Yong (S10257760G)
// Team Member 2: Joey Tan Ying Xian (S10262534D) 

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Actor.h"
#include "Movie.h"
#include "Vector.h"
#include "ActorGraph.h"
#include "HashTable.h"
#include <iomanip> 
#include "AVLTree.h"
#include <ctime>

using namespace std;
void displayUserMenu();
void displayAdminMenu();
void displaySelectUser();
void addRelationship(HashTable<Actor>* actors, HashTable<Movie>* movies);
void handleUserFunctions(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph);
void updateActorsCSV(HashTable<Actor>* actorhash);
void updateMoviesCSV(HashTable<Movie>* movieHash);
void handleAdminFunction(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph);
void addKnownActorsFromCast(ActorGraph* actors, HashTable<Movie>* movieHash); 
int partition(Vector<Movie*> movies, int left, int right);
void sortMovies(Vector<Movie*> movies, int left, int right);
int partitionActors(Vector<Actor*> actors, int left, int right);
void sortActors(Vector<Actor*> actors, int left, int right);

Vector<string> splitCSVLine(const string& line) {
	Vector<string> result;
	stringstream ss(line);
	string field;
	bool inQuotes = false;

	// splits the whole csv line at the comma 
	while (getline(ss, field, ',')) {
		// Check if the field contains is quoted "\"Hang-ro(course): Jeju, Joseon, Osaka"\" or \" Hello "\
		// this is to check if the string is quoted but is a subpart of the whole quote
		if (!field.empty() && field.front() == '"' && field.back() != '"') {
			inQuotes = true;
			result.pushBack(field);  // Using custom Vector's pushBack method
			continue;
		}

		if (inQuotes) {
			// Add the current field to the previous one and keep looking
			string& lastField = result[result.getLength() - 1]; // take the last item in the vector 
			lastField += "," + field; // concatenate the last field with curent field 
			if (field.back() == '"') {
				inQuotes = false;
			}
		}
		else {
			result.pushBack(field);  // the field does not contain quotes (add to result vector)
		}
	}
	return result;
}


int main() {
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
		// Use the custom split function to correctly split the CSV line
		Vector<string> columns = splitCSVLine(line);

		// Make sure to have at least 4 columns
		if (columns.getLength() >= 4) {
			string movId = columns[0];
			string movTitle = columns[1];
			string movPlot = columns[2];
			string movYear = columns[3];
            // Convert to integers
            int movieId = stoi(movId);
            int movRYear = stoi(movYear);
			// Create Movie object and add it to hash table
			Movie* newMovie = new Movie(movieId, movTitle, movPlot, movRYear);
			movieHashTable->add(movRYear, newMovie);
        }
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
		Actor* newActor = new Actor(aid, actorName, actorBirthYear);
		actorHashTable->add(actorBirthYear, newActor);
		// find the actor 
		AVLNode<Actor>* actorNode = actorHashTable->search(aid);
		if (actorNode != nullptr) {
			Actor* actorPtr = actorNode->item;
			actorGraph->addActor(actorPtr);
		}


		//actor.displayInfo();

	}

	actorStream.close();
	// Insert the relationship between the actors and the movies 
	addRelationship(actorHashTable, movieHashTable);

	//actorGraph->printAdjacencyList();
	cout << "Welcome to the movie database" << endl;
	while (true) {
		displaySelectUser();
		cout << "Enter your Option: " << endl;
		int useOption;
		cin >> useOption;
		if (useOption == 1) {
			handleUserFunctions(actorHashTable, movieHashTable, actorGraph);
		}
		else if (useOption == 2) {
			handleAdminFunction(actorHashTable,movieHashTable,actorGraph);
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
			if (movieNode != nullptr && actorNode != nullptr) {
				Movie* moviePtr = movieNode->item;
				Actor* actorPtr = actorNode->item;

				// push_back the movie to the actor
				movieNode->relatedPointers.pushBack(actorPtr);
				actorNode->relatedPointers.pushBack(moviePtr);
			}
			else {
				cout << "Null" << endl;
			}
		}
		castStream.close();

	}

	else {
		cout << "The file given is not opened";
	}

}

// Precondition: The actor HashTable is not null, and the cast csv is also not empty 
// Postcondition: Add all known actors to a graph called actorGraph based on the given condition stated in the requirements both actors stared in the same movie or an actor knows another actor through a middleman (actor A2)
// Time Complexity: O(n)^3
// For each actor maintain a list of vectors that will add actors belonging to the same movie 


// Refactor the code to traverse the movieHashTable instead and retrieving all movieNodes
// Use vector to store all movie nodes 
void addKnownActorsFromCast(ActorGraph* actors, HashTable<Movie>* movieHash) {
	Vector<AVLNode<Movie>*> movieNodeList;
	movieHash->getAll(movieNodeList);
	if (movieNodeList.getLength() > 0) {
		// loop through
		for (int i = 0; i < movieNodeList.getLength(); i++) {
			AVLNode<Movie>* m = movieNodeList[i];
			Vector<Actor*> actorCast = m->relatedPointers;
			for (int j = 0; j < actorCast.getLength(); j++) {
				Actor* currentActor = actorCast[j];
				for (int h = j + 1; h < actorCast.getLength(); h++) {
					Actor* nextActor = actorCast[h];
					actors->addRelation(currentActor->getKey(), nextActor->getKey());
				}
			}

		}
	}
	else {
		cout << "There is no movies in the list" << endl;
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
	cout << "---- Select an admin feature -----" << endl;
	cout << "[1] Add new actor" << endl;
	cout << "[2] Add new movie" << endl;
	cout << "[3] add an actor to a movie" << endl;
	cout << "[4] Update actor/movie details" << endl;
	cout << "[0] Exit" << endl;
	cout << "---------------------------------" << endl;
}

void displayUserMenu() {
	cout << "-------------------------------- Select a user feature ---------------------------------" << endl;
	cout << "[1] Display (in ascending order of age) the actors with age between x and y (inclusive)" << endl;
	cout << "[2] Display movies made within the past 3 years (in ascending order of year)" << endl;
	cout << "[3] Display all movies an actor starred in (in alphabetical order)" << endl;
	cout << "[4] Display all the actors in a particular movie (in alphabetical order)" << endl;
	cout << "[5] Display a list of all actors that a particular actor knows." << endl;
	cout << "[0] to exit" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
}

void handleUserFunctions(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph) {
	while (true) {
		displayUserMenu();
		cout << endl;
		int option;
		cout << "Enter the option to choose" << endl;
		cin >> option;

		// Display actors who are in the age range
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
			time_t t = time(0);
			struct tm now;
			localtime_s(&now, &t); // Safely populate now with the current time
			int currentYear = now.tm_year + 1900;  // Get the current year
			int oldestAge = stoi(oldAge);
			int olderBirthYear = currentYear - oldestAge;
			int youngerBirthYear = currentYear - youngestAge;
			cout << left << setw(10) << "Actor Id"
				<< left << setw(25) << "Actor Name"
				<< left << setw(25) << "Actor Birth Year"
				<< left << setw(25) << "Actor's age"
				<< endl;
			for (int i = youngerBirthYear; i > olderBirthYear; i--) {
				// call the getKey function 
				AVLTree<Actor>* avlTreePtr = actorhash->getKey(i);
				// print the items 
				if (avlTreePtr->getRoot() != nullptr) {
					avlTreePtr->print();
				}
			}

		}

		// Diplay movie in the past 3 years
		else if (option == 2) {
			cout << "Enter a year: ";
			int yearEntered;
			cin >> yearEntered;
			int lowYear = yearEntered - 3;
			cout << left << setw(10) << "MovieId"
				<< left << setw(100) << "MovieTitle"
				<< left << setw(40) << "MoviePlot"
				<< left << setw(10) << "Released Year"
				<< endl;
			for (int i = lowYear; i <= yearEntered; i++) {
				AVLTree<Movie>* avlMoviePtr = movieHash->getKey(i);
				avlMoviePtr->print();
				cout << endl;
			}

		}

		// Display all movies an actors starred in
		else if (option == 3) {
			// retrieve all actors first 
			cout << "Enter the actor name: ";
			string actorName;
			cin.ignore();
			getline(cin, actorName);
			AVLNode<Actor>* actorAVL = actorhash->searchByName(actorName);
			if (actorAVL != nullptr) {
				Vector<Movie*> movies;
				movies = actorAVL->relatedPointers;
				sortMovies(movies, 0, movies.getLength() - 1);

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

		// Display all the actors in a particular movie
		else if (option == 4) {
			// retrieve all movies first 
			cout << "Enter the name of the specific movie: ";
			string movieName;
			cin.ignore();
			getline(cin, movieName);
			cout << movieName << endl;
			AVLNode<Movie>* movieAVL = movieHash->searchByName(movieName);
			if (movieAVL != nullptr) {
				Vector<Actor*> cast;
				cast = movieAVL->relatedPointers;
				sortActors(cast, 0, cast.getLength() - 1);
				if (cast.getLength() > 0) {
					cout << left << setw(10) << "Actor Id"
						<< left << setw(25) << "Actor Name"
						<< left << setw(25) << "Actor Birth Year"
						<< left << setw(25) << "Actor's age"
						<< endl;
					for (int i = 0; i < cast.getLength(); i++) {
						Actor* a = cast[i];
						a->displayInfo();
					}
				}

			}
		}

		// Display a list of all actors that a particular actor know
		// Additional feature: Using implementation of known actors using graphs
		else if (option == 5) {
			// Insert known actors into the graph 
			addKnownActorsFromCast(actorgraph, movieHash);
			cout << "Enter the actor's name: " << endl;
			string name;
			cin.ignore();
			getline(cin, name);
			int actorInd = actorgraph->getActorByName(name);
			actorgraph->displayAllRelatedActors(actorInd);

		}

		else if (option == 0) {
			break;
		}
	}

}

int partition(Vector<Movie*> movies, int left, int right) {
	Movie* pivot = movies[(left + right) / 2];
	while (left < right) {
		while (movies[left]->getName() < pivot->getName()) {
			left++; // increase the left index 
		}
		while (movies[right]->getName() > pivot->getName()) {
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
		sortMovies(movies, left, q - 1); // left
		sortMovies(movies, q + 1, right); // right
	}
	else {
		return;
	}
}
// quickSort implementation for actors (thing is triggered here)
int partitionActors(Vector<Actor*> actors, int left, int right) {
	Actor* pivot = actors[(left + right) / 2];
	while (left <= right) {
		while (actors[left]->getName() < pivot->getName()) {
			//cout << "Sorting" << actors[left]->getName() <<  " and " << pivot->getName() << endl;
			left++; // increase the left index 
		}
		while (actors[right]->getName() > pivot->getName()) {
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
		sortActors(actors, q + 1, right); // right
	}
	else {
		return;
	}
}

// Update Actor.CSV File
void updateActorsCSV(HashTable<Actor>* actorhash) {
	ofstream actorFile("actors.csv", ios::trunc);

	if (!actorFile.is_open()) {
		cout << "Error opening actors.csv!" << endl;
		return;
	}

	actorFile << "ActorID,ActorName,BirthYear\n";  // Write CSV header

	for (int i = 0; i < 101; i++) {
		AVLTree<Actor>* actorTree = actorhash->getKey(i);
		if (actorTree && actorTree->getRoot() != nullptr) {
			AVLNode<Actor>* current = actorTree->getRoot();
			while (current) {
				actorFile << current->item->getKey() << ","
					<< current->item->getName() << ","
					<< current->item->getYear() << "\n";
				current = current->right;
			}
		}
	}
	actorFile.close();
	cout << "Actors file updated!" << endl;
}

// Update Movies.CSV File
void updateMoviesCSV(HashTable<Movie>* movieHash) {
	ofstream movieFile("movies.csv", ios::trunc);

	if (!movieFile.is_open()) {
		cout << "Error opening movies.csv!" << endl;
		return;
	}

	movieFile << "MovieID,MovieTitle,MoviePlot,ReleasedYear\n";

	for (int i = 0; i < 101; i++) {
		AVLTree<Movie>* movieTree = movieHash->getKey(i);
		if (movieTree && movieTree->getRoot() != nullptr) {
			AVLNode<Movie>* current = movieTree->getRoot();
			while (current) {
				movieFile << current->item->getKey() << ","
					<< current->item->getName() << ","
					<< current->item->getYear() << "\n";
				current = current->right;
			}
		}
	}
	movieFile.close();
	cout << "Movies file updated!" << endl;
}

// Administrator features
void handleAdminFunction(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorGraph) {
	while (true) {
		displayAdminMenu();
		int option;
		cout << "Enter your option: ";
		cin >> option;

		// Adding New Actor
		if (option == 1) {
			cout << "Add new actor" << endl;
			int actorId, birthYear;
			string actorName;
			cin.ignore();
			cout << "Enter Actor ID: ";
			cin >> actorId;
			cin.ignore();
			cout << "Enter Actor Name: ";
			getline(cin, actorName);
			cout << "Enter Birth Year: ";
			cin >> birthYear;

			Actor* newActor = new Actor(actorId, actorName, birthYear);
			actorhash->add(birthYear, newActor);
			actorGraph->addActor(newActor);
			//updateActorsCSV(actorhash);

			cout << "New actor added successfully!" << endl;
		}

		// Adding New Movie
		else if (option == 2) {
			cout << "Add new movie" << endl;
			int movieId, releasedYear;
			string movieTitle, moviePlot;

			cout << "Enter Movie ID: ";
			cin >> movieId;
			cin.ignore();
			cout << "Enter Movie Title: ";
			getline(cin, movieTitle);
			cout << "Enter Movie Plot: ";
			getline(cin, moviePlot);
			cout << "Enter Release Year: ";
			cin >> releasedYear;

			Movie* newMovie = new Movie(movieId, movieTitle, moviePlot, releasedYear);
			movieHash->add(releasedYear, newMovie);
			//updateMoviesCSV(movieHash);

			cout << "New movie added successfully!" << endl;
		}

		// Adding Actor to a Movie
		else if (option == 3) {
			cout << "Add an actor to a movie" << endl;
			int actorId, movieId;
			cout << "Enter Actor ID: ";
			cin >> actorId;
			cout << "Enter Movie ID: ";
			cin >> movieId;

			AVLNode<Movie>* movieNode = movieHash->search(movieId);
			AVLNode<Actor>* actorNode = actorhash->search(actorId);

			if (movieNode && actorNode) {
				Movie* moviePtr = movieNode->item;
				Actor* actorPtr = actorNode->item;

				movieNode->relatedPointers.pushBack(actorPtr);
				actorNode->relatedPointers.pushBack(moviePtr);

				cout << "Actor added to the movie successfully!" << endl;
			}
			else {
				cout << "Actor or Movie not found!" << endl;
			}
		}

		// Updating Actor/Movie Details
		else if (option == 4) {
			cout << "Update actor/movie details" << endl;
			int choice;
			cout << "Update (1) Actor or (2) Movie? ";
			cin >> choice;

			// When user wants to update actor details
			if (choice == 1) {
				int actorId;
				cout << "Enter Actor ID: ";
				cin >> actorId;
				AVLNode<Actor>* actorNode = actorhash->search(actorId);
				Vector<Movie*> actedMovies = actorNode->relatedPointers;
				actorNode->item->displayInfo();
				if (actorNode) {
					Actor* temp = actorNode->item;
					cout << "Enter New Name: ";
					cin.ignore();
					string newName;
					getline(cin, newName);
					cout << "Enter New Birth Year: ";
					int newBirthYear;
					cin >> newBirthYear;

					actorhash->remove(actorNode->item->getYear(),actorNode->key);
					temp->setActorName(newName);
					temp->setActorBirthYear(newBirthYear);
					actorhash->add(newBirthYear, temp);
					// get the new actor 
					actorNode = actorhash->search(actorId);
					for (int i = 0; i < actedMovies.getLength(); i++) {
						actorNode->relatedPointers.pushBack(actedMovies[i]);
					}
				}
				else {
					cout << "Actor not found!" << endl;
				}
			}

			// When user wants to update movies details
			else if (choice == 2) {
				int movieId;
				cout << "Enter Movie ID: ";
				cin >> movieId;

				AVLNode<Movie>* movieNode = movieHash->search(movieId);
				if (movieNode) {
					Vector<Actor*> cast = movieNode->relatedPointers;
					Movie* temp = movieNode->item;
					cout << "Enter New Title: ";
					cin.ignore();
					string newTitle;
					getline(cin, newTitle);
					cout << "Enter New Release Year: ";
					int newYear;
					cin >> newYear;

					movieHash->remove(temp->getKey(), movieNode->key);
					temp->setMovieTitle(newTitle);
					temp->setReleasedYear(newYear);
					movieHash->add(newYear, temp);
					// get the new movie
					movieNode = movieHash->search(movieId);
				}
				else {
					cout << "Movie not found!" << endl;
				}
			}
		}

		else if (option == 0) {
			break;
		}
		else {
			cout << "Invalid Option" << endl;
		}
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
