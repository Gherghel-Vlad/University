#pragma once
#include "DynamicVector.h"
#include "Movie.h"
#include "MoviesRepository.h"
#include "File.h"
#include <vector>


class UserServiceException : public exception {
private:
	string message;
	
public:
	UserServiceException(string message) : message{ message } {

	}

	const char* what() const noexcept override;

};

class UserService {
	private:
		MoviesRepository& mr;
		int currentIndex;
		vector<Movie> watchList;
		File* file;
public:

	/// <summary>
	/// Constructor for the user service class
	/// </summary>
	/// <param name="mr">Reference to the instance of Movies repository</param>
	UserService(MoviesRepository& mr);
	
	/// <summary>
	/// copy constructor
	/// </summary>
	UserService(const UserService& us): mr(us.mr) {
		this->currentIndex = us.currentIndex;
		this->watchList = us.watchList;
	}
	
	/// <summary>
	/// Operator = manifestation
	/// </summary>
	int operator=(const UserService& us) {
		this->mr = us.mr;
		this->currentIndex = us.currentIndex;
		this->watchList = us.watchList;
	}

	/// <summary>
	/// destructor
	/// </summary>
	~UserService();

	vector<Movie> getWatchListAsVector() {
		return this->watchList;
	}

	/// <summary>
	/// Adds a movie to the watch list if it wasnt added already
	/// </summary>
	/// <param name="movie">Instance of the movie to add</param>
	void addMovieToWatchList(Movie movie);

	/// <summary>
	/// Gets the next movie from the list starting from the current count having the given genre (string, leave empty for all movies)
	/// </summary>
	/// <param name="genre"> The given genre to search for (leave empty to show all)</param>
	/// <returns>An instance of the movie, the result of the search, or throws error if it didnt</returns>
	Movie getCurrentMovieToShowToUser(string genre);

	/// <summary>
	/// Deletes a movie from the watchlist and depepnding of the value of like it will increase the number of likes of that movie or not
	/// </summary>
	/// <param name="index">The position from the watchlist of which movie to delete</param>
	/// <param name="like">If it s true, it will increase the number of likes of the movie that will be deleted, it wont if it s false</param>
	void deleteMovieFromWatchList(int index, bool like = false);

	/// <summary>
	/// reutrns the string representation of the watchlist
	/// </summary>
	/// <returns>String representation of the watchlist</returns
	string getWatchListString();

	/// <summary>
	/// Restarts the showing of movies for the user from the beginning
	/// </summary>
	void restartFromStart();


	/// <summary>
	/// Writes the list of movies in the file given by the file name
	/// </summary>
	/// <param name="fileName">The name of the file to write in</param>
	void writeToFile(string fileName = "user_watchlist.txt");

	/// <summary>
	/// Reads the data from the given file
	/// </summary>
	/// <param name="fileName">The file name of the file from which to read the data</param>
	void readFromFile(string fileName = "user_watchlist.txt");

	void setFile(File* f);

	void openFile();

};