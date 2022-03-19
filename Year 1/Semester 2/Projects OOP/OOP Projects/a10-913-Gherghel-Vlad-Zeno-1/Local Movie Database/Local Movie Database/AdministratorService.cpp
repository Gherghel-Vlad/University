#include "AdministratorService.h"
#include "Validators.h"
#include "Command.h"
#include "AddCommand.h"
#include "DeleteCommand.h"
#include "UpdateCommand.h"
#include "UndoRedoService.h"

AdministratorService::AdministratorService(MoviesRepository& mr): moviesRepo(mr) {
	UndoRedoService* a = new UndoRedoService(this);
	this->undoRedoService = a;
}
/// <summary>
/// Adds a movie to the repo (checks the data aswell)
/// </summary>
/// <param name="movie">Movie instance</param>
void AdministratorService::addMovie(Movie movie, bool calledFromUndoRedoService) {

	Validators::checkMovie(movie);

	if (this->moviesRepo.getIndexOfMovieWithTitle(movie.getTitle()) != -1)
		throw AdministratorServiceException("Movie with given title exists already");
	if (calledFromUndoRedoService == false) {
		this->undoRedoService->addUndoCommand(new AddCommand(this, movie));
	}
	this->moviesRepo.addMovie(movie);
}

/// <summary>
/// delete the movie from the given position
/// </summary>
/// <param name="pos">The position to be deleted from</param>
void AdministratorService::deleteMovieFromPosition(int pos, bool calledFromUndoRedoService) {
	if (calledFromUndoRedoService == false) {
		this->undoRedoService->addUndoCommand(new DeleteCommand(this, this->moviesRepo.getAllMoviesAsVector()[pos]));
	}
	this->moviesRepo.deleteMovieByIndex(pos);
}

/// <summary>
/// delete the movie with the given title
/// </summary>
/// <param name="title">The given title (string)</param>
void AdministratorService::deleteMovieWithTitle(string title, bool calledFromUndoRedoService) {
	Validators::checkTitle(title);

	int pos;
	pos = this->moviesRepo.getIndexOfMovieWithTitle(title);
	if (pos == -1)
		throw AdministratorServiceException("Movie with the given title doesn't exists.");
	if (calledFromUndoRedoService == false) {
		this->undoRedoService->addUndoCommand(new DeleteCommand(this, this->moviesRepo.getAllMoviesAsVector()[pos]));
	}
	this->moviesRepo.deleteMovieByIndex(pos);
}


/// <summary>
/// updates the movie from the given position with the given movie
/// </summary>
/// <param name="new_movie">Instance of the new movie to be put in the given position</param>
/// <param name="pos">The given index/position to be updated</param>
void AdministratorService::updateMovieFromPositionn(Movie new_movie, int pos, bool calledFromUndoRedoService) {
	Validators::checkMovie(new_movie);

	if (this->moviesRepo.getIndexOfMovieWithTitle(new_movie.getTitle(), pos) != -1)
		throw AdministratorServiceException("Movie with given title exists already");

	if (calledFromUndoRedoService == false) {
		this->undoRedoService->addUndoCommand(new UpdateCommand(this, this->moviesRepo.getAllMoviesAsVector()[pos], new_movie));
	}
	this->moviesRepo.updateMovie(new_movie, pos);
}

/// <summary>
/// Update the movie with the given title
/// </summary>
/// <param name="new_movie">The new instance of the movie to be updated with</param>
/// <param name="title">The title to be searched for</param>
void AdministratorService::updateMovieWithTitle(Movie new_movie, string title, bool calledFromUndoRedoService) {
	Validators::checkMovie(new_movie);
	Validators::checkTitle(title);

	int pos;
	pos = this->moviesRepo.getIndexOfMovieWithTitle(title);
	if (pos == -1)
		throw AdministratorServiceException("Movie with the given title doesn't exists.");
	
	if (this->moviesRepo.getIndexOfMovieWithTitle(new_movie.getTitle(), pos) != -1)
		throw AdministratorServiceException("Movie with the new given title exists already");
	if (calledFromUndoRedoService == false) {
		this->undoRedoService->addUndoCommand(new UpdateCommand(this, this->moviesRepo.getAllMoviesAsVector()[pos], new_movie));
	}
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