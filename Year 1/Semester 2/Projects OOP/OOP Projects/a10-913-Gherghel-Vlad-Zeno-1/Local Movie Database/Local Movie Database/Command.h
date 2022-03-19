#pragma once
#include "AdministratorService.h"

class Command
{
public:

	virtual void undo() = 0;

	virtual void redo() = 0;
};
