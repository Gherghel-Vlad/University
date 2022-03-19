#pragma once
#include "File.h"
#define FILENAME "watch_list.html"

class  HTMLFile : public File
{
public:
	string toStringMovie(Movie*) const override;

	void saveToFile(const std::vector<Movie>) const override;

	void openFile() override;


};

