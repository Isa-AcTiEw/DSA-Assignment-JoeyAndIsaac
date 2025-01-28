#pragma once
#include <string>
using namespace std;
class Movie
{
	private:
		int movieId;
		string movieTitle;
		string moviePlot;
		int releasedYear;
	public:
		// Public methods, getterrs and setters and constructor 
		Movie();  // default constructor 
		Movie(int mId, string mTitle, string mPlot, int mReleasedYear); // parameterized constructor 
		void setReleasedYear(int rYear);
		void setMovieTitle(string mTitle);
		int getReleasedYear();
		int getKey();
		void displayInfo();

};

