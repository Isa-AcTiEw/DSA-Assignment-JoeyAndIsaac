#include "Movie.h"
#include <iostream>
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

int Movie::getReleasedYear() {
	return releasedYear;
}


int Movie::getKey() {
	return movieId;
}

void Movie::displayInfo() {
	cout << "MovieId: " << " " << movieId << endl;
	cout << "Movie Title:  " << " " << movieTitle << endl;
	cout << "Year of release: " << " " << releasedYear << endl;
}