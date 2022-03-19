#include "AddCommand.h"

void AddCommand::undo()
{
	this->as->deleteMovieWithTitle(this->addedMovie.getTitle(), true);
}

void AddCommand::redo()
{
	this->as->addMovie(this->addedMovie, true);
}
