#pragma once
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
		Movie(int mId, int rYear, string mTitle); // parameterized constructor 
		void setReleasedYear(int rYear);
		void setMovieTitle(string mTitle);
		int getReleasedYear();
		int getKey();
		void displayInfo();

};

