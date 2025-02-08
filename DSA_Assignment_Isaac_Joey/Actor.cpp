#include "Actor.h"
#include <iomanip>  
#include <ctime>
#include <iostream>
using namespace std;
Actor::Actor() {};
Actor::Actor(int aId, string aName, int bYear) {
	actorId = aId;
	actorName = aName;
	birthYear = bYear;
};
int Actor::getKey() {
	return actorId;
};

string Actor::getName() {
	return actorName;
};


void Actor::setActorName(string aName) {
	 actorName = aName;
}
void Actor::setActorBirthYear(int bYear) {
	birthYear = bYear;
};

int Actor::getActorBirthYear() {
	return birthYear;
}
void Actor::displayInfo() {
	cout << left << setw(10) << actorId
		<< left << setw(25) << actorName
		<< left << setw(25) << birthYear
		<< left << setw(25) << calculateAge()
		<< endl;
};

int Actor::calculateAge() {
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t); // Safely populate now with the current time

	int currentYear = now.tm_year + 1900;  // Get the current year
	return currentYear - birthYear; // Use the correct current year
}