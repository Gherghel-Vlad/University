#include "MoviesRepository.h"

#include <sstream>
/// <summary>
/// Adds a movie to the repo
/// </summary>
/// <param name="movie">Instance of the movie</param>
void MoviesRepository::addMovie(Movie movie) {
	this->moviesDV.add(movie);
}

/// <summary>
/// Deletes a movie from the repo on given position
/// </summary>
/// <param name="pos">Index of movie to delete.</param>
void MoviesRepository::deleteMovieByIndex(int pos) {
	this->moviesDV.deleteElementByIndex(pos);
}

/// <summary>
/// Updates a movie on a given position
/// </summary>
/// <param name="new_movie">The new instance of the movie that will be at that position</param>
/// <param name="pos">The index of the movie to be updated</param>
void MoviesRepository::updateMovie(Movie new_movie, int pos) {
	this->moviesDV.updateElement(new_movie, pos);
}

/// <summary>
/// Creates a string containing all the movies represented beautiful
/// </summary>
/// <returns>returns a string containing all the movies represented beautiful</returns>
string MoviesRepository::toString() {
	stringstream txt;

	for (int i = 0; i < this->moviesDV.getSize(); i++) {
		txt << i << " " << this->moviesDV.getAllElements()[i].toString() << '\n';
	}
	return txt.str();
}

/// <summary>
/// returns the index if it exists, false otherwise (pos is for ignoring that position, used in update on the adminsitrator service
/// </summary>
/// <param name="title">The title to search for</param>
/// <param name="pos">The index to be ommitted from the search</param>
/// <returns> The index if it was found, or -1 if it wasnt</returns>
int MoviesRepository::getIndexOfMovieWithTitle(string title, int pos) {
	
	for (int i = 0; i < this->moviesDV.getSize(); i++) {
		if (i != pos && title == this->moviesDV.getAllElements()[i].getTitle())
			return i;
	}
	return -1;

}