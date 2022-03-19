

#include "Validators.h"

void Validators::checkTitle(string title) {
	if (title == "")
		throw ValidatorsException("Invalid title.");
}

void Validators::checkGenre(string genre) {
	if (genre == "")
		throw ValidatorsException("Invalid genre.");
}

void Validators::checkYearOfRelease(int yearOfRelease) {
	if (yearOfRelease < 1800)
		throw ValidatorsException("Invalid year of release.");
}

void Validators::checkNumberOfLikes(int nrOfLikes) {
	if (nrOfLikes < 0)
		throw ValidatorsException("Invalid number of likes.");

}

void Validators::checkTrailer(string trailer) {
	if (trailer == "")
		throw ValidatorsException("Invalid trailer link.");
}

void Validators::checkMovie(Movie movie) {
	Validators::checkTitle(movie.getTitle());
	Validators::checkGenre(movie.getGenre());
	Validators::checkYearOfRelease(movie.getYearOfRelease());
	Validators::checkNumberOfLikes(movie.getNumberOfLikes());
	Validators::checkTrailer(movie.getTrailer());
}




const char* ValidatorsException::what() const noexcept {
	return this->message.c_str();
}