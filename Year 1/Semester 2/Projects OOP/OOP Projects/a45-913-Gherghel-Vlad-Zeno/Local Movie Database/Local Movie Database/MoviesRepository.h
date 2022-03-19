#pragma once

#include "DynamicVector.h"
#include "Movie.h"
#include <vector>

class MoviesRepository {

private:
	std::vector<Movie> moviesDV{};

public:
	// default constructor
	MoviesRepository() {}

	// copy function
	MoviesRepository(const MoviesRepository& mr) {
		this->moviesDV = mr.moviesDV;
	}

	// destructor
	~MoviesRepository() {}


	/// <summary>
	/// Adds a movie to the repo
	/// </summary>
	/// <param name="movie">Instance of the movie</param>
	void addMovie(Movie movie);

	/// <summary>
	/// Deletes a movie from the repo on given position
	/// </summary>
	/// <param name="pos">Index of movie to delete.</param>
	void deleteMovieByIndex(int pos);

	/// <summary>
	/// Updates a movie on a given position
	/// </summary>
	/// <param name="new_movie">The new instance of the movie that will be at that position</param>
	/// <param name="pos">The index of the movie to be updated</param>
	void updateMovie(Movie new_movie, int pos);

	/// <summary>
	/// returns the number of movies in the array
	/// </summary>
	/// <returns>INteger representing the number of movies in the repo</returns>
	int getNumberOfMovies() { return moviesDV.size(); }

	/// <summary>
	/// Returns the array of movies
	/// </summary>
	/// <returns>Returns the array of movies</returns>
	Movie* getAllMovies() { return &moviesDV[0]; }

	/// <summary>
	/// Gets the index of a movie
	/// </summary>
	/// <param name="movie">The movie instance to search for</param>
	/// <returns>THe index (int) if it was found, -1 otherwise</returns>
	int getIndexOfMovie(Movie movie) { return moviesDV.getIndexOfElement(movie); }


	/// <summary>
	/// returns the index if it exists, false otherwise (pos is for ignoring that position, used in update on the adminsitrator service
	/// </summary>
	/// <param name="title">The title to search for</param>
	/// <param name="pos">The index to be ommitted from the search</param>
	/// <returns> The index if it was found, or -1 if it wasnt</returns>
	int getIndexOfMovieWithTitle(string title, int pos = -1);
	
	/// <summary>
	/// Creates a string containing all the movies represented beautiful
	/// </summary>
	/// <returns>returns a string containing all the movies represented beautiful</returns>
	string toString();
};
