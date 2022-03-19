#pragma once

#include <string>

using namespace std;

class Movie {
private:
	string title;
	string genre;
	int yearOfRelease;
	int numberOfLikes;
	string trailer;

public:
	// default constructor
	Movie();

	// constructor
	Movie(string title, string genre, int yearOfRelease, int numberOfLikes, string trailer);


	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="movie">Movie instance</param>
	Movie(const Movie& movie);


	/// <summary>
	/// Destructor for the movie instance
	/// </summary>
	~Movie();

	
	/// <summary>
	/// Title getter
	/// </summary>
	/// <returns>Title (string)</returns>
	string getTitle() { return this->title; }

	/// <summary>
	/// Title setter
	/// </summary>
	/// <param name="new_title">New title to be set with (string)</param>
	void setTitle(string new_title) { this->title = new_title; }


	/// <summary>
	/// Genre getter
	/// </summary>
	/// <returns>Genre (string)</returns>
	string getGenre() { return this->genre; }

	/// <summary>
	/// Genre setter
	/// </summary>
	/// <param name="new_genre">New genre to be set with (string)</param>
	void setGenre(string new_genre) { this->genre = new_genre; }


	/// <summary>
	/// Year of release getter
	/// </summary>
	/// <returns>Year of release (int)</returns>
	int getYearOfRelease() { return this->yearOfRelease; }

	/// <summary>
	/// Year of release setters
	/// </summary>
	/// <param name="new_year_of_release">New year of release to be set with (int)</param>
	void setYearOfRelease(int new_year_of_release) { this->yearOfRelease = new_year_of_release; }

	/// <summary>
	/// Number of likes getter
	/// </summary>
	/// <returns>Number of likes (int)</returns>
	int getNumberOfLikes() { return this->numberOfLikes; }

	/// <summary>
	/// Number of likes setter
	/// </summary>
	/// <param name="new_number_of_likes">New number of likes to be set with (int)</param>
	void setNumberOfLikes(int new_number_of_likes) { this->numberOfLikes = new_number_of_likes; }

	/// <summary>
	/// Trailer getter
	/// </summary>
	/// <returns>Trailer (string)</returns>
	string getTrailer() { return this->trailer; }

	/// <summary>
	/// Trailer setter
	/// </summary>
	/// <param name="new_trailer">New trailer to be set with (string)</param>
	void setTrailer(string new_trailer) { this->trailer = new_trailer; }


	/// <summary>
	/// Creates a string representation of the movie
	/// </summary>
	/// <returns>A string representation of the movie elements</returns>
	string toString();


	/// <summary>
	/// Operator overloading
	/// </summary>
	/// <param name="v">Instance of the movie</param>
	/// <returns>True if they are equal, false otherwise</returns>
	bool operator==(const Movie& v) const ;
	


	/// <summary>
	/// Assing operator overloading
	/// </summary>
	/// <param name="v">The right left instance of the movie</param>
	/// <returns>A new instance of the movie</returns>
	Movie& operator=(const Movie& v);

};





