#include "Movie.h"
#include <iostream>
#include <iomanip>
using namespace std;
Movie::Movie() {};
Movie::Movie(int mId, string mTitle, string mPlot, int mReleasedYear) {
	movieId = mId;
	movieTitle = mTitle;
	moviePlot = mPlot;
	releasedYear = mReleasedYear;
};

void Movie::setReleasedYear(int rYear) {
	releasedYear = rYear;
}

void Movie::setMovieTitle(string mTitle) {
	movieTitle = mTitle;
}

string Movie::getMovieTitle() {
	return movieTitle;
}

int Movie::getReleasedYear() {
	return releasedYear;
}


int Movie::getKey() {
	return movieId;
}

void Movie::displayInfo() {
	cout << left << setw(10) << movieId
		<< left << setw(25) << movieTitle
		<< left << setw(10) << releasedYear
		<< endl;
}