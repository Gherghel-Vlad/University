#pragma once
#include <string>
#include "Movie.h"
using namespace std;

class Validators {

public:

	/// <summary>
	/// Checks the validity of a title (string)
	/// </summary>
	/// <param name="title">The title to be checked (string)</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkTitle(string title);

	/// <summary>
	/// Checks the validity of a genre (string)
	/// </summary>
	/// <param name="genre">The genre to be checked (string)</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkGenre(string genre);

	/// <summary>
	/// Checks the validity of a year of release
	/// </summary>
	/// <param name="yearOfRelease">The year of release to be checked (int)</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkYearOfRelease(int yearOfRelease);

	/// <summary>
	/// Checks the validity of a number of likes
	/// </summary>
	/// <param name="nrOfLikes">The number of likes to be checked (int)</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkNumberOfLikes(int nrOfLikes);

	/// <summary>
	/// Checks the validity of a trailer (string)
	/// </summary>
	/// <param name="trailer">The trailer to be checked (string)</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkTrailer(string trailer);

	/// <summary>
	/// Checks the validity of a movie
	/// </summary>
	/// <param name="movie">The instance of the movie to be checked</param>
	/// <returns>True if it's a good one, false otherwise</returns>
	static bool checkMovie(Movie movie);
};


