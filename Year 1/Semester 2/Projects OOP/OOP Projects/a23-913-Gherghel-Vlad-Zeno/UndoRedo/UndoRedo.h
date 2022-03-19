//
// Created by Admin on 3/17/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_UNDOREDO_H
#define A23_913_GHERGHEL_VLAD_ZENO_UNDOREDO_H
#include "../Domain/DynamicArray.h"

typedef struct {
	DynamicArray* da_undo;
	DynamicArray* da_redo;
	int current_position_undo;
	int current_position_redo;
} UndoRedo;

UndoRedo* create_undo_redo();

void add_list_undo_redo(UndoRedo* ur, DynamicArray* da);

void undo(UndoRedo* ur, DynamicArray** da);

void redo(UndoRedo* ur, DynamicArray** da);

void destroy_undo_redo(UndoRedo* ur);

#endif //A23_913_GHERGHEL_VLAD_ZENO_UNDOREDO_H
