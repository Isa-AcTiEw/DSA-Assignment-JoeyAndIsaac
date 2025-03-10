// Team Member 1: Isaac Tiew Xun Yong (S10257760G)
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
		void setMoviePlot(string mPlot);
		int getYear();
		int getKey();
		string getName();
		string getMoviePlot();
		void displayInfo();

};

