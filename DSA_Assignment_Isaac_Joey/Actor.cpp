#include "Actor.h"
#include <iomanip>  
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

int Actor::getActorBirthYear() {
	return birthYear;
}

void Actor::setActorName(string aName) {
	 actorName = aName;
}
void Actor::setActorBirthYear(int bYear) {
	birthYear = bYear;
};
void Actor::displayInfo() {
	cout << left << setw(10) << actorId
		 << left << setw(25) << actorName
		 << left << setw(10) << birthYear
		 << endl;
};
