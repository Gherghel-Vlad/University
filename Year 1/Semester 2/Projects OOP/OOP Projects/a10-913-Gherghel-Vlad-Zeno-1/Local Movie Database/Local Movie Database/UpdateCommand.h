#pragma once
#include "Command.h"
class UpdateCommand: public Command
{
private:
	AdministratorService* as;
	Movie oldMovie;
	Movie newMovie;

public:

	UpdateCommand(AdministratorService* as, Movie oldMovie, Movie newMovie) : as(as) {
		this->oldMovie = oldMovie;
		this->newMovie = newMovie;
	}

	void undo() override;

	void redo() override;

};

