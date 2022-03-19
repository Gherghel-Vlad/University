#include "AdministratorService.h"
#include "Validators.h"

/// <summary>
/// Adds a movie to the repo (checks the data aswell)
/// </summary>
/// <param name="movie">Movie instance</param>
void AdministratorService::addMovie(Movie movie) {
	Validators::checkMovie(movie);

	if (this->moviesRepo.getIndexOfMovieWithTitle(movie.getTitle()) != -1)
		throw AdministratorServiceException("Movie with given title exists already");

	this->moviesRepo.addMovie(movie);
}

/// <summary>
/// delete the movie from the given position
/// </summary>
/// <param name="pos">The position to be deleted from</param>
void AdministratorService::deleteMovieFromPosition(int pos) {
	this->moviesRepo.deleteMovieByIndex(pos);
}

/// <summary>
/// delete the movie with the given title
/// </summary>
/// <param name="title">The given title (string)</param>
void AdministratorService::deleteMovieWithTitle(string title) {
	Validators::checkTitle(title);

	int pos;
	pos = this->moviesRepo.getIndexOfMovieWithTitle(title);
	if (pos == -1)
		throw AdministratorServiceException("Movie with the given title doesn't exists.");

	this->moviesRepo.deleteMovieByIndex(pos);
}


/// <summary>
/// updates the movie from the given position with the given movie
/// </summary>
/// <param name="new_movie">Instance of the new movie to be put in the given position</param>
/// <param name="pos">The given index/position to be updated</param>
void AdministratorService::updateMovieFromPositionn(Movie new_movie, int pos) {
	Validators::checkMovie(new_movie);

	if (this->moviesRepo.getIndexOfMovieWithTitle(new_movie.getTitle(), pos) != -1)
		throw AdministratorServiceException("Movie with given title exists already");

	this->moviesRepo.updateMovie(new_movie, pos);
}

/// <summary>
/// Update the movie with the given title
/// </summary>
/// <param name="new_movie">The new instance of the movie to be updated with</param>
/// <param name="title">The title to be searched for</param>
void AdministratorService::updateMovieWithTitle(Movie new_movie, string title) {
	Validators::checkMovie(new_movie);
	Validators::checkTitle(title);

	int pos;
	pos = this->moviesRepo.getIndexOfMovieWithTitle(title);
	if (pos == -1)
		throw AdministratorServiceException("Movie with the given title doesn't exists.");
	
	if (this->moviesRepo.getIndexOfMovieWithTitle(new_movie.getTitle(), pos) != -1)
		throw AdministratorServiceException("Movie with the new given title exists already");

	this->moviesRepo.updateMovie(new_movie, pos);
}

/// <summary>
/// Get the string representation of all the movies
/// </summary>
/// <returns>String representation of all the movies</returns>
string AdministratorService::getStringRepresentationOfMovies() {
	return this->moviesRepo.toString();
}


const char* AdministratorServiceException::what() const noexcept {
	return this->message.c_str();
}