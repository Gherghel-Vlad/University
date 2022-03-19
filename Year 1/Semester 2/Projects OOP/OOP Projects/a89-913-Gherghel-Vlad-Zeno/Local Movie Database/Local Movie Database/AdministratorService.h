#pragma once
#include "MoviesRepository.h"
#include "Movie.h"

class AdministratorServiceException : public exception {
private:
	string message;
public:
	AdministratorServiceException(string message) : message{ message } {

	}

	const char* what() const noexcept override;

};



class AdministratorService {
private:
	MoviesRepository& moviesRepo;

public:

	// constructor that gets the movies repo to work on
	AdministratorService(MoviesRepository& mr): moviesRepo(mr) {
	}

	AdministratorService(const AdministratorService& as): moviesRepo(as.moviesRepo) {
	}

	// destructor
	~AdministratorService() {};

	vector<Movie> getAllMovies() {
		return this->moviesRepo.getAllMoviesAsVector();
	}

	/// <summary>
	/// Adds a movie to the repo (checks the data aswell)
	/// </summary>
	/// <param name="movie">Movie instance</param>
	void addMovie(Movie movie);


	/// <summary>
	/// delete the movie from the given position
	/// </summary>
	/// <param name="pos">The position to be deleted from</param>
	void deleteMovieFromPosition(int pos);


	/// <summary>
	/// updates the movie from the given position with the given movie
	/// </summary>
	/// <param name="new_movie">Instance of the new movie to be put in the given position</param>
	/// <param name="pos">The given index/position to be updated</param>
	void updateMovieFromPositionn(Movie new_movie, int pos);


	/// <summary>
	/// delete the movie with the given title
	/// </summary>
	/// <param name="title">The given title (string)</param>
	void deleteMovieWithTitle(string title);

	/// <summary>
	/// Get the string representation of all the movies
	/// </summary>
	/// <returns>String representation of all the movies</returns>
	string getStringRepresentationOfMovies();


	/// <summary>
	/// Update the movie with the given title
	/// </summary>
	/// <param name="new_movie">The new instance of the movie to be updated with</param>
	/// <param name="title">The title to be searched for</param>
	void updateMovieWithTitle(Movie new_movie, string title);


};
