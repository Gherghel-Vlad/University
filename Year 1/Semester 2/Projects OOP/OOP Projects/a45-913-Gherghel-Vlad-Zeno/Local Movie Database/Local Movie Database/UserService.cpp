
#include "UserService.h"
#include "Movie.h"
#include "DynamicVector.h"
#include "Validators.h"
#include <iostream>
#include <sstream>

using namespace std;

/// <summary>
/// Constructor for the user service class
/// </summary>
/// <param name="mr">Reference to the instance of Movies repository</param>
UserService::UserService(MoviesRepository& mr) : mr(mr) {
	this->currentIndex = -1;
	this->watchList = DynamicVector<Movie>{5};
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
	if (this->watchList.getIndexOfElement(movie) != -1) {
		throw "Movie already exists in the watchlist!\n";
	}

	this->watchList.add(movie);
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
		throw "No movies with the given genre exist";
	}
}

/// <summary>
/// Deletes a movie from the watchlist and depepnding of the value of like it will increase the number of likes of that movie or not
/// </summary>
/// <param name="index">The position from the watchlist of which movie to delete</param>
/// <param name="like">If it s true, it will increase the number of likes of the movie that will be deleted, it wont if it s false</param>
void UserService::deleteMovieFromWatchList(int index, bool like) {

	if (index < 0 || index >= this->watchList.getSize()) {
		throw "Index out of range!";
	}

	if (like == true) {
		// increasing the number of likes
		this->mr.getAllMovies()[this->mr.getIndexOfMovie(this->watchList[index])].setNumberOfLikes(this->mr.getAllMovies()[this->mr.getIndexOfMovie(this->watchList[index])].getNumberOfLikes() + 1);
	
	}
	
	this->watchList.deleteElementByIndex(index);


}

/// <summary>
/// reutrns the string representation of the watchlist
/// </summary>
/// <returns>String representation of the watchlist</returns>
string UserService::getWatchListString() {
	std:stringstream txt;
	int i;
	if (this->watchList.getSize() > 0) {
		for (i = 0; i < this->watchList.getSize(); i++) {
			txt << i << " " << this->watchList.getAllElements()[i].toString() << "\n";
		}
	}
	return txt.str();
}

