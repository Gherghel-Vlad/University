#include "CSVFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


string CSVFile::toStringMovie(Movie* movie) const {
	std::stringstream buffer;

	buffer << movie->getTitle() << "," << movie->getGenre() << "," << movie->getYearOfRelease() << "," << movie->getNumberOfLikes() << "," << movie->getTrailer() << "\n";
	
	return buffer.str();
}



void CSVFile::saveToFile(const vector<Movie> moviesVector) const{
	ofstream f(FILENAME);

	if (!f.is_open()) {
		return;
	}

	for (auto movie : moviesVector)
		f << this->toStringMovie(&movie);

	f.close();
}

void CSVFile::openFile() {
	std::string fileName = std::string(FILENAME);
	fileName = "notepad \"" + fileName + "\"";
	system(fileName.c_str());
}
