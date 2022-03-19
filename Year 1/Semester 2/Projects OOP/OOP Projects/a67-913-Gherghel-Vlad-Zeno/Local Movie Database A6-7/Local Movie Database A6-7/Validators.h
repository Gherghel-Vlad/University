#pragma once
#include <string>
#include "Movie.h"
using namespace std;

class ValidatorsException : public exception {
private:
	string message;
public:
	ValidatorsException(string message) : message{ message } {

	}

	const char* what() const noexcept override;
};


class Validators {

public:

	/// <summary>
	/// Checks the validity of a title (string)
	/// </summary>
	/// <param name="title">The title to be checked (string)</param>
	static void checkTitle(string title);

	/// <summary>
	/// Checks the validity of a genre (string)
	/// </summary>
	/// <param name="genre">The genre to be checked (string)</param>
	static void checkGenre(string genre);

	/// <summary>
	/// Checks the validity of a year of release
	/// </summary>
	/// <param name="yearOfRelease">The year of release to be checked (int)</param>
	static void checkYearOfRelease(int yearOfRelease);

	/// <summary>
	/// Checks the validity of a number of likes
	/// </summary>
	/// <param name="nrOfLikes">The number of likes to be checked (int)</param>
	static void checkNumberOfLikes(int nrOfLikes);

	/// <summary>
	/// Checks the validity of a trailer (string)
	/// </summary>
	/// <param name="trailer">The trailer to be checked (string)</param>
	static void checkTrailer(string trailer);

	/// <summary>
	/// Checks the validity of a movie
	/// </summary>
	/// <param name="movie">The instance of the movie to be checked</param>
	static void checkMovie(Movie movie);
};


