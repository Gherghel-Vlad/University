
#include "UserService.h"
#include "Movie.h"
#include "DynamicVector.h"
#include "Validators.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#define FILENAME "user_watchlist.txt"
using namespace std;

/// <summary>
/// Constructor for the user service class
/// </summary>
/// <param name="mr">Reference to the instance of Movies repository</param>
UserService::UserService(MoviesRepository& mr) : mr(mr) {
	this->currentIndex = -1;
	this->readFromFile(FILENAME);
}

/// <summary>
/// destructor
/// </summary>
UserService::~UserService() {
}

/// <summary>
/// Adds a movie to the watch list if it wasnt added already
/// </summary>
/// <param name="movie">Instance of the movie to add</param>
void UserService::addMovieToWatchList(Movie movie) {
	if ( find(this->watchList.begin(), this->watchList.end(), movie) != this->watchList.end()) {
		throw UserServiceException("Movie already exists in the watchlist!\n");
	}

	this->watchList.push_back(movie);
	this->writeToFile(FILENAME);
}

/// <summary>
/// Restarts the showing of movies for the user from the beginning
/// </summary>
void UserService::restartFromStart() {
	this->currentIndex = -1;
}

/// <summary>
/// Gets the next movie from the list starting from the current count having the given genre (string, leave empty for all movies)
/// </summary>
/// <param name="genre"> The given genre to search for (leave empty to show all)</param>
/// <returns>An instance of the movie, the result of the search, or throws error if it didnt</returns>
Movie UserService::getCurrentMovieToShowToUser(string genre) {
	int countMovies = 0;
	if (genre == "") {
		if (this->currentIndex == this->mr.getNumberOfMovies() -1) {
			this->currentIndex = 0;
		}
		else {
			this->currentIndex++;
		}
		return this->mr.getAllMovies()[this->currentIndex];
	}
	else {
		while (countMovies < this->mr.getNumberOfMovies()) {
			if (this->currentIndex == this->mr.getNumberOfMovies() -1) {
				this->currentIndex = 0;
			}
			else {
				this->currentIndex++;
			}
			countMovies++;
			if (this->mr.getAllMovies()[this->currentIndex].getGenre().find(genre) != string::npos) {
				return this->mr.getAllMovies()[this->currentIndex];
			}
		}
		throw UserServiceException("No movies with the given genre exist");
	}
}

/// <summary>
/// Deletes a movie from the watchlist and depepnding of the value of like it will increase the number of likes of that movie or not
/// </summary>
/// <param name="index">The position from the watchlist of which movie to delete</param>
/// <param name="like">If it s true, it will increase the number of likes of the movie that will be deleted, it wont if it s false</param>
void UserService::deleteMovieFromWatchList(int index, bool like) {

	if (index < 0 || index >= this->watchList.size()) {
		throw UserServiceException("Index out of range!");
	}

	if (like == true) {
		// increasing the number of likes
		this->mr.getAllMovies()[this->mr.getIndexOfMovie(this->watchList[index])].setNumberOfLikes(this->mr.getAllMovies()[this->mr.getIndexOfMovie(this->watchList[index])].getNumberOfLikes() + 1);
		this->mr.writeToFile();
	}
	
	this->watchList.erase(this->watchList.begin() + index);
	this->writeToFile(FILENAME);


}

/// <summary>
/// reutrns the string representation of the watchlist
/// </summary>
/// <returns>String representation of the watchlist</returns>
string UserService::getWatchListString() {
	std:stringstream txt;
	int i = 0;
	if (this->watchList.size() > 0) {
		for (auto movie : this->watchList) {
			txt << i << " " << movie.toString() << "\n";
			i++;
		}
	}
	return txt.str();
}

/// <summary>
/// Writes the list of movies in the file given by the file name
/// </summary>
/// <param name="fileName">The name of the file to write in</param>
void UserService::writeToFile(string fileName) {
	ofstream f(fileName);

	if (!f.is_open()) {
		return;
	}

	for (auto movie : this->watchList)
		f << movie;

	f.close();

	this->file->saveToFile(this->watchList);
}


/// <summary>
/// Reads the data from the given file
/// </summary>
/// <param name="fileName">The file name of the file from which to read the data</param>
void UserService::readFromFile(string fileName) {
	ifstream inFile(fileName);

	if (!inFile.is_open()) {
		return;
	}
	Movie movie{};

	while (inFile >> movie) {
		this->watchList.push_back(movie);
	}

	inFile.close();
}


void UserService::setFile(File* f) {

	this->file = f;

}

void UserService::openFile() {
	this->writeToFile();
	this->file->openFile();
}

const char* UserServiceException::what() const noexcept {
	return this->message.c_str();
}