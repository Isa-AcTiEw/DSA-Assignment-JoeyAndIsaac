#pragma once
#include "Data.h"
#include <string>
using namespace std;
class Movie
{
	private:
		int movieId;
		int releasedYear;
		string movieTitle;
	public:
		// Public methods, getterrs and setters and constructor 
		Movie();  // default constructor 
		Movie(int mId, string rYear, string mTitle); // parameterized constructor 
		void setReleasedYear();
		void setMovieTitle();
		int getReleasedYear();
		int getKey();
		void displayInfo();

};

