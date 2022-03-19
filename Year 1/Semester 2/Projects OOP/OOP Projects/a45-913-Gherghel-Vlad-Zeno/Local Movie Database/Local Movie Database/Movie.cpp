
#include "Movie.h"
#include <iostream>
#include <sstream>

/// <summary>
/// Defauly constructor
/// </summary>
Movie::Movie() {}

/// <summary>
/// Constructor with full parameters
/// </summary>
/// <param name="title">The title of the movie</param>
/// <param name="genre">The genre of the movie</param>
/// <param name="yearOfRelease">The year of release of the movie</param>
/// <param name="numberOfLikes">The number of likes of the movie</param>
/// <param name="trailer">A link to the movie's trailer</param>
Movie::Movie(string title, string genre, int yearOfRelease, int numberOfLikes, string trailer) {
	this->title = title;
	this->genre = genre;
	this->yearOfRelease = yearOfRelease;
	this->numberOfLikes = numberOfLikes;
	this->trailer = trailer;
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="movie">Movie instance</param>
Movie::Movie(const Movie& movie) {
	this->title = movie.title;
	this->genre = movie.genre;
	this->yearOfRelease = movie.yearOfRelease;
	this->numberOfLikes = movie.numberOfLikes;
	this->trailer = movie.trailer;
}

/// <summary>
/// Destructor for the movie instance
/// </summary>
Movie::~Movie() {
	//std::cout << "Destructor";
}

/// <summary>
/// Creates a string representation of the movie
/// </summary>
/// <returns>A string representation of the movie elements</returns>
std::string Movie::toString() {
	std::stringstream txt;
	txt << "Title: " << this->title << " Genre: " << this->genre << " Year of release: " << this->yearOfRelease << " Number of likes: " << this->numberOfLikes << " Trailer: " << this->trailer;
	return txt.str();
}

/// <summary>
/// Operator overloading
/// </summary>
/// <param name="v">Instance of the movie</param>
/// <returns>True if they are equal, false otherwise</returns>
bool Movie::operator==(const Movie& v) const {
		return (v.title == this->title && v.genre == this->genre && v.yearOfRelease == this->yearOfRelease && v.numberOfLikes == this->numberOfLikes && v.trailer == this->trailer);
	}

/// <summary>
/// Assing operator overloading
/// </summary>
/// <param name="v">The right left instance of the movie</param>
/// <returns>A new instance of the movie</returns>
Movie& Movie::operator=(const Movie& v) {
	this->title = v.title;
	this->genre = v.genre;
	this->yearOfRelease = v.yearOfRelease;
	this->numberOfLikes = v.numberOfLikes;
	this->trailer = v.trailer;
	return *this;
}