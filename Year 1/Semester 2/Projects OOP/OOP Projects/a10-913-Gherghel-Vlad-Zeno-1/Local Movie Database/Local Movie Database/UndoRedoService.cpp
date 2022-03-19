#include "UndoRedoService.h"
#include "Command.h"


void UndoRedoService::addUndoCommand(Command* c) {
	this->redoStack.clear();

	this->undoStack.push_back(c);
}

void UndoRedoService::addRedoCommand(Command* c) {
	this->redoStack.push_back(c);
}

bool UndoRedoService::executeUndoCommand() {

	if (this->undoStack.empty()) {
		return false;
	}

	Command* c = this->undoStack.back();
	this->redoStack.push_back(c);
	c->undo();
	this->undoStack.pop_back();
	return true;
}

bool UndoRedoService::executeRedoCommand() {
	if (this->redoStack.empty()) {
		return false;
	}
	Command* c = this->redoStack.back();
	this->undoStack.push_back(c);
	this->redoStack.pop_back();
	c->redo();

	return true;
}