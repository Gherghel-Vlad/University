#pragma once
#include "Command.h"
#include <deque>
using namespace std;
class AdministratorService;
class UndoRedoService
{
private:
	deque<Command*> undoStack;
	deque<Command*> redoStack;
	AdministratorService* as = nullptr;

public:
	UndoRedoService(AdministratorService* asf) {
		this->as = asf;
	}

	void addUndoCommand(Command* c);

	void addRedoCommand(Command* c);

	bool executeUndoCommand();

	bool executeRedoCommand();
};

