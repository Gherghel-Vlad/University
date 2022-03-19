#pragma once
#include "Command.h"

class DeleteCommand: public Command
{
private:
	AdministratorService* as;
	Movie deletedMovie;

public:

	DeleteCommand(AdministratorService* as, Movie deletedMovie) : as(as) {
		this->deletedMovie = deletedMovie;
	}

	void undo() override;

	void redo() override;

};

