#include "Movie.h"
#include <iostream>
using namespace std;
Movie::Movie() {};
Movie::Movie(int mId, int rYear, string mTitle) {
	movieId = mId,
	releasedYear = rYear;
	movieTitle = mTitle;
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
	return releasedYear;
}

void Movie::displayInfo() {
	cout << "MovieId: " << " " << movieId << endl;
	cout << "Movie Title:  " << " " << movieTitle << endl;
	cout << "Year of release: " << " " << releasedYear << endl;
}