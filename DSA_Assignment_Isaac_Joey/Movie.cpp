// Team Member 1: Isaac Tiew Xun Yong (S10257760G)
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

void Movie::setMoviePlot(string mPlot) {
	moviePlot = mPlot;
}

string Movie::getName() {
	return movieTitle;
}

string Movie::getMoviePlot() {
	return moviePlot;
}

int Movie::getYear() {
	return releasedYear;
}


int Movie::getKey() {
	return movieId;
}

void Movie::displayInfo() {
	cout << left << setw(10) << movieId
		<< left << setw(100) << movieTitle
		<< left << setw(40) << moviePlot
		<< left << setw(10) << releasedYear
		<< endl;
}