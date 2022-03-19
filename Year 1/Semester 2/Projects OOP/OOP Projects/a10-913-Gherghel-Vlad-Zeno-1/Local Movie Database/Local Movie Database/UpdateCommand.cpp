#include "UpdateCommand.h"

void UpdateCommand::undo()
{
	this->as->updateMovieWithTitle(this->oldMovie, this->newMovie.getTitle(), true);
}

void UpdateCommand::redo()
{
	this->as->updateMovieWithTitle(this->newMovie, this->oldMovie.getTitle(), true);
}
