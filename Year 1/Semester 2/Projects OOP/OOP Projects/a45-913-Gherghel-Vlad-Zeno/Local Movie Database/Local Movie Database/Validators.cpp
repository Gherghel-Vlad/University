

#include "Validators.h"

bool Validators::checkTitle(string title) {
	if (title == "")
		return false;
	return true;
}

bool Validators::checkGenre(string genre) {
	if (genre == "")
		return false;
	return true;
}

bool Validators::checkYearOfRelease(int yearOfRelease) {
	if (yearOfRelease < 1800)
		return false;
	return true;
}

bool Validators::checkNumberOfLikes(int nrOfLikes) {
	if (nrOfLikes < 0)
		return false;
	return true;

}

bool Validators::checkTrailer(string trailer) {
	if (trailer == "")
		return false;
	return true;
}

bool Validators::checkMovie(Movie movie) {
	return (Validators::checkTitle(movie.getTitle()) && Validators::checkGenre(movie.getGenre()) && Validators::checkYearOfRelease(movie.getYearOfRelease()) && Validators::checkNumberOfLikes(movie.getNumberOfLikes()) && Validators::checkTrailer(movie.getTrailer()));
}



