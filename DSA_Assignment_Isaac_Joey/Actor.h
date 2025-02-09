#pragma once
#include <string>
using namespace std;
class Actor
{
	private:
		int actorId;
		string actorName;
		int birthYear;
	public:
		Actor(); // default constructor 
		Actor(int aId, string aName, int bYear);
		// getters and setters for the classes 
		int getKey();
		int getYear();
		string getName();
		void setActorName(string aName);
		void setActorBirthYear(int bYear);
		void displayInfo();
		int calculateAge();
};

