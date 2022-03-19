//
// Created by Admin on 3/17/2021.
//

#include "UndoRedo.h"
#include <stdlib.h>
#include "../Repository/OffersRepoDA.h"

/// <summary>
/// Creates a deep copy of the given array
/// </summary>
/// <param name="da">The dynamic array to be copied</param>
/// <returns>A poitner to the newly created dynamic array</returns>
DynamicArray* get_copy_of_dynamic_array(DynamicArray* da) {
	DynamicArray* copy_da = create_dynamic_array(da->capacity, destroy_offer, copy_offer);

	Offer* elem, * o;

	for (int i = 0; i < da->length; i++) {
		elem = da->elems[i];
		o = create_offer(elem->type, elem->destination, elem->departure_date, elem->price);
		add_element_dynamic_array(copy_da, o);
		destroy_offer(o);
	}

	return copy_da;
}

/// <summary>
/// Constructor for the struct
/// </summary>
/// <returns>A poitner to the newly created constructor</returns>
UndoRedo* create_undo_redo() {
	UndoRedo* ur = (UndoRedo*)malloc(sizeof(UndoRedo));

	ur->da_undo = create_dynamic_array(20, destroy_dynamic_array, get_copy_of_dynamic_array);
	ur->da_redo = create_dynamic_array(20, destroy_dynamic_array, get_copy_of_dynamic_array);
	ur->current_position_undo = 0;
	ur->current_position_redo = 0;
}



/// <summary>
/// Adds to the list of undoes
/// </summary>
/// <param name="ur">The ur instance</param>
/// <param name="da">The dynimac array instance to be added</param>
void add_list_undo_redo(UndoRedo* ur, DynamicArray* da) {
	if (ur == NULL || da == NULL)
		return;
	int i;
	if (ur->current_position_undo < ur->da_undo->length)
	{
		destroy_dynamic_array(ur->da_undo);
	}
	ur->da_undo->length = ur->current_position_undo;
	add_element_dynamic_array(ur->da_undo, da);
	ur->current_position_undo++;


	destroy_dynamic_array(ur->da_redo);
	ur->da_redo = create_dynamic_array(20, destroy_dynamic_array, get_copy_of_dynamic_array);
	ur->current_position_redo = 0;
}

/// <summary>
/// Adds a dynamic list to the list of redoes
/// </summary>
/// <param name="ur">The instance of the under redo</param>
/// <param name="da">The isntance of the dynamic array</param>
void add_list_undo_redo_redo(UndoRedo* ur, DynamicArray* da) {
	if (ur == NULL || da == NULL)
		return;
	int i;
	if (ur->current_position_redo != 0)
	{
		destroy_dynamic_array(ur->da_redo);
	}
	ur->da_redo->length = ur->current_position_redo;
	add_element_dynamic_array(ur->da_redo, da);
	ur->current_position_redo++;
}

/// <summary>
/// Undoes the last operation
/// </summary>
/// <param name="ur">The instance of the undo redo struct</param>
/// <param name="da">The adress of the instance of the dynamic</param>
void undo(UndoRedo* ur, DynamicArray** da) {
	DynamicArray* da1;
	DynamicArray* da2;
	if (ur->current_position_undo > 0) {
		add_list_undo_redo_redo(ur, *da);
		da2 = *da;
		da1 = ur->da_undo->copy_function(ur->da_undo->elems[ur->current_position_undo - 1]);
		*da = da1;
		destroy_dynamic_array(da2);
		ur->current_position_undo--;
	}
}

/// <summary>
/// Redoes the last undoed operation
/// </summary>
/// <param name="ur"></param>
/// <param name="da"></param>
void redo(UndoRedo* ur, DynamicArray** da) {
	DynamicArray* da1;
	DynamicArray* da2;
	if (ur->current_position_redo > 0) {
		da2 = *da;
		da1 = ur->da_redo->copy_function(ur->da_redo->elems[ur->current_position_redo - 1]);
		*da = da1;
		destroy_dynamic_array(da2);
		ur->current_position_redo--;
	}
}

/// <summary>
/// Deconstructor for the undo redo struct
/// </summary>
/// <param name="ur">The instance of the undo redo struct</param>
void destroy_undo_redo(UndoRedo* ur) {
	destroy_dynamic_array(ur->da_redo);
	destroy_dynamic_array(ur->da_undo);
	free(ur);
}