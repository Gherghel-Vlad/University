#include "MoviesRepository.h"

#include <sstream>
#include <fstream>
/// <summary>
/// Adds a movie to the repo
/// </summary>
/// <param name="movie">Instance of the movie</param>
void MoviesRepository::addMovie(Movie movie) {
	this->moviesDV.push_back(movie);
	this->writeToFile(FILENAME);
}

/// <summary>
/// Deletes a movie from the repo on given position
/// </summary>
/// <param name="pos">Index of movie to delete.</param>
void MoviesRepository::deleteMovieByIndex(int pos) {
	if (pos < 0 || pos >= this->moviesDV.size())
		throw MoviesRepositoryException("Invalid index.");

	this->moviesDV.erase(this->moviesDV.begin() + pos);
	this->writeToFile(FILENAME);
}

/// <summary>
/// Updates a movie on a given position
/// </summary>
/// <param name="new_movie">The new instance of the movie that will be at that position</param>
/// <param name="pos">The index of the movie to be updated</param>
void MoviesRepository::updateMovie(Movie new_movie, int pos) {
	if (pos < 0 || pos >= this->moviesDV.size())
		throw MoviesRepositoryException("Invalid index.");

	this->moviesDV[pos] = new_movie;
	this->writeToFile(FILENAME);
}

/// <summary>
/// Creates a string containing all the movies represented beautiful
/// </summary>
/// <returns>returns a string containing all the movies represented beautiful</returns>
string MoviesRepository::toString() {
	stringstream txt;
	int count = 0;
	for (auto movie : this->moviesDV) {
		txt << count << " " << movie.toString() << '\n';
		count++;
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
	int count = 0;
	for (auto movie : this->moviesDV) {
		if (count != pos && title == movie.getTitle())
			return count;
		count++;
	}
	return -1;

}

/// <summary>
/// Gets the index of a movie
/// </summary>
/// <param name="movie">The movie instance to search for</param>
/// <returns>THe index (int) if it was found, -1 otherwise</returns>
int MoviesRepository::getIndexOfMovie(Movie movie) {
	auto pos = find(this->moviesDV.begin(), this->moviesDV.end(), movie);

	if (pos != this->moviesDV.end())
		return pos - this->moviesDV.begin();
	return -1;
}



/// <summary>
/// Writes the list of movies in the file given by the file name
/// </summary>
/// <param name="fileName">The name of the file to write in</param>
void MoviesRepository::writeToFile(string fileName) {
	ofstream f(fileName);

	if (!f.is_open()) {
		return;
	}
	for( auto movie : this->moviesDV)
		f << movie;

	f.close();
}


/// <summary>
/// Reads the data from the given file
/// </summary>
/// <param name="fileName">The file name of the file from which to read the data</param>
void MoviesRepository::readFromFile(string fileName) {
	ifstream inFile(fileName);

	if (! inFile.is_open()) {
		return;
	}
	Movie movie{};

	while (inFile >> movie) {
		this->moviesDV.push_back(movie);
	}

	inFile.close();
}



ostream& operator<<(ostream& os, const MoviesRepository& moviesRepo) {
	stringstream strStream;

	for (auto movie : moviesRepo.moviesDV) {
		strStream << movie;
	}

	os << strStream.str();
	return os;
}

istream& operator>>(istream& is, MoviesRepository& moviesRepo) {

	return is;

}


const char* MoviesRepositoryException::what() const noexcept {
	return message.c_str();
}
