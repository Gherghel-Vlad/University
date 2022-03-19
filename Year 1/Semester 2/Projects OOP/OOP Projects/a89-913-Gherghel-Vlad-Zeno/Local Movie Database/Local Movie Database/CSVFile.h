#pragma once
#include "Movie.h"
#include "File.h"
#include <vector>
#define FILENAME "watch_list.csv"

class CSVFile : public File
{
public:
	string toStringMovie(Movie* movie) const override;

	void saveToFile(const std::vector<Movie>) const override;

	void openFile() override;

};
