#include "DeleteCommand.h"

void DeleteCommand::undo()
{
	this->as->addMovie(this->deletedMovie, true);
}

void DeleteCommand::redo()
{
	this->as->deleteMovieWithTitle(this->deletedMovie.getTitle(), true);
}
