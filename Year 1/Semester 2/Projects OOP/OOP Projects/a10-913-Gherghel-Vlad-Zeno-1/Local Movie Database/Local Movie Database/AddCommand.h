#pragma once
#include "Command.h"

class AddCommand : public Command
{
private:
	AdministratorService* as;
	Movie addedMovie;

public:

	AddCommand(AdministratorService* as, Movie addedMovie): as(as)  {
		this->addedMovie = addedMovie;
	}

	void undo() override;

	void redo() override;
};


