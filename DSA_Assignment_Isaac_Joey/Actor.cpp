#include "Actor.h"
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

string Actor::getActorName() {
	return actorName;
};
void Actor::setActorName(string aName) {
	 actorName = aName;
}
void Actor::setActorBirthYear(int bYear) {
	birthYear = bYear;
};
void Actor::displayInfo() {
	cout << "Actor's Id: " << " " << actorId << endl;
	cout << "Actor's name: " << " " << actorName << endl;
	cout << "Actor's birth year: " << " " << birthYear << endl;
};
