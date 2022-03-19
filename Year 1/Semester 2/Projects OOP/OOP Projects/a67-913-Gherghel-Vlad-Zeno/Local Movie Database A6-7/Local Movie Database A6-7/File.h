#pragma once
#include <string>
#include <vector>
#include "Movie.h"

class File {

public:
	virtual string toStringMovie(Movie*) const=0;

	virtual void saveToFile(const std::vector<Movie>) const=0;

	virtual void openFile()=0;
};
