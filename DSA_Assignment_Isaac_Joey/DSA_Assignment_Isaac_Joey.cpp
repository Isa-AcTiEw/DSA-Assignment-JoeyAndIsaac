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
#include <iomanip> 
#include "AVLTree.h"
#include <ctime>
using namespace std;
void displayMenu();
void displayUserMenu();
void displayAdminMenu();
void displaySelectUser();
void addRelationship(HashTable<Actor>* actors, HashTable<Movie>* movies);
void handleUserFunctions(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash, ActorGraph* actorgraph);
void updateActorsCSV(HashTable<Actor>* actorhash);
void updateMoviesCSV(HashTable<Movie>* movieHash);
void handleAdminFunction(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash);
void addKnownActorsFromCast(ActorGraph* actors, HashTable<Movie>* movieHash); 
int partition(Vector<Movie*> movies, int left, int right);
void sortMovies(Vector<Movie*> movies, int left, int right);
int partitionActors(Vector<Actor*> actors, int left, int right);
void sortActors(Vector<Actor*> actors, int left, int right);
void checkForUnormalisedData(string& title);

void checkForUnormalisedData(string& title) {
	// Check if the title contains double quotes and remove them
	if (title.find('"') != std::string::npos) {
		title.erase(std::remove(title.begin(), title.end(), '"'), title.end());
	}

}
Vector<string> splitCSVLine(const string& line) {
	Vector<string> result;
	stringstream ss(line);
	string field;
	bool inQuotes = false;

	while (getline(ss, field, ',')) {
		// If the field starts with a quote and does not end with one, it's a quoted field
		if (!field.empty() && field.front() == '"' && field.back() != '"') {
			inQuotes = true;
			result.pushBack(field);  // Using custom Vector's pushBack method
			continue;
		}

		if (inQuotes) {
			// Add the current field to the previous one and keep looking
			string& lastField = result[result.getLength() - 1];  // Using custom operator[] and getLength
			lastField += "," + field;

			if (field.back() == '"') {
				inQuotes = false;
			}
		}
		else {
			result.pushBack(field);  // Using custom Vector's pushBack method
		}
	}

	return result;
}


int main() {
	string name = "\"Hang-ro(course): Jeju, Joseon, Osaka\"";
	checkForUnormalisedData(name);
	cout << "This is name: " << name << endl;
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
		string movId, movTitle, movPlot, movYear;

		// Extract each field of the movie separated by the comma delimiter 
		getline(ss, movId, ',');   // Movie ID
		getline(ss, movTitle, ','); // Movie Title
		getline(ss, movPlot, ','); // Movie Plot
		getline(ss, movYear, ','); // Release Year

		checkForUnormalisedData(movTitle);
		cout << "Movie id: " << movId << endl;
		cout << "Year Released: " << movYear << endl;
		int movieId = stoi(movId);
		int movRYear = stoi(movYear);

		// Create Movie object and add it to hash table
		Movie movie(movieId, movTitle, movPlot, movRYear);
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
		cout << "This is actor id: " << aid << endl;
		if (actorName.find('"', actorName.length())) {
			actorName.erase(std::remove(actorName.begin(), actorName.end(), '"'), actorName.end());
		}
		actorName.erase(std::remove(actorName.begin(), actorName.end(), '"'), actorName.end());
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

	actorGraph->printAdjacencyList();
	cout << "Welcome to the movie database" << endl;
	while (true) {
		displaySelectUser();
		cout << "Enter your Option: " << endl;
		int useOption;
		cin >> useOption;
		if (useOption == 1) {
			handleUserFunctions(actorHashTable,movieHashTable,actorGraph);
		}
		else if (useOption == 2) {
			handleAdminFunction(actorHashTable, movieHashTable);
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
			cout << "This is the movieTitle: " << m->item.getName() << endl;
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
			cout << "Enter the actor name: ";
			string actorName;
			cin.ignore();
			getline(cin, actorName);
			AVLNode<Actor>* actorAVL = actorhash->searchByName(actorName); 
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
			cout << "Enter the name of the specific movie: ";
			string movieName;
			cin.ignore();
			getline(cin,movieName);
			cout << movieName << endl;
			AVLNode<Movie>* movieAVL = movieHash->searchByName(movieName);
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
		else if (option == 5) {
			cout << "Enter the actor's name: " << endl;
			string name;
			cin.ignore();
			getline(cin,name);
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
		while (actors[left]->getName() < pivot->getName()) {
			cout << "Sorting" << actors[left]->getName() <<  " and " << pivot->getName() << endl;
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
		sortActors(actors, q+1, right); // right
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
				actorFile << current->item.getKey() << ","
					<< current->item.getName() << ","
					<< current->item.getActorBirthYear() << "\n";
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
				movieFile << current->item.getKey() << ","
					<< current->item.getName() << ","
					<< current->item.getReleasedYear() << "\n";
				current = current->right;
			}
		}
	}
	movieFile.close();
	cout << "Movies file updated!" << endl;
}

// Administrator features
void handleAdminFunction(HashTable<Actor>* actorhash, HashTable<Movie>* movieHash) {
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

			cout << "Enter Actor ID: ";
			cin >> actorId;
			cin.ignore();
			cout << "Enter Actor Name: ";
			getline(cin, actorName);
			cout << "Enter Birth Year: ";
			cin >> birthYear;

			Actor newActor(actorId, actorName, birthYear);
			actorhash->add(birthYear, newActor);
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

			Movie newMovie(movieId, movieTitle, moviePlot, releasedYear);
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
				Movie* moviePtr = &(movieNode->item);
				Actor* actorPtr = &(actorNode->item);

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

			if (choice == 1) {
				int actorId;
				cout << "Enter Actor ID: ";
				cin >> actorId;

				AVLNode<Actor>* actorNode = actorhash->search(actorId);
				if (actorNode) {
					Actor temp = actorNode->item;

					cout << "Enter New Name: ";
					cin.ignore();
					string newName;
					getline(cin, newName);
					cout << "Enter New Birth Year: ";
					int newBirthYear;
					cin >> newBirthYear;

					actorhash->remove(temp.getKey());
					temp.setActorName(newName);
					temp.setActorBirthYear(newBirthYear);
					actorhash->add(newBirthYear, temp);
					//updateActorsCSV(actorhash);
				}
				else {
					cout << "Actor not found!" << endl;
				}
			}
			else if (choice == 2) {
				int movieId;
				cout << "Enter Movie ID: ";
				cin >> movieId;

				AVLNode<Movie>* movieNode = movieHash->search(movieId);
				if (movieNode) {
					Movie temp = movieNode->item;

					cout << "Enter New Title: ";
					cin.ignore();
					string newTitle;
					getline(cin, newTitle);
					cout << "Enter New Release Year: ";
					int newYear;
					cin >> newYear;

					movieHash->remove(temp.getKey());
					temp.setMovieTitle(newTitle);
					temp.setReleasedYear(newYear);
					movieHash->add(newYear, temp);
					//updateMoviesCSV(movieHash);
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
