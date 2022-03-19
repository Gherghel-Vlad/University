//
// Created by Admin on 3/9/2021.
//

#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

/// Creates a dynamic array with the given capacity, which will use destroyer_function to destroy elements and copy_function to copy them
/// \param capacity The initial capacity of the dynamic vector
/// \param destroyer_function The function that frees an element from this array (destroyer(void*))
/// \param copy_function The function that returns a new pointer to a new element created using an already existing element (copy_function(void*))
/// \return A pointer to the new dynamic array created
DynamicArray *create_dynamic_array(int capacity, void *destroyer_function, void *copy_function) {
    DynamicArray *da = (DynamicArray *) malloc(sizeof(DynamicArray));
    if (da == NULL || destroyer_function == NULL || copy_function == NULL)
        return NULL;

    da->length = 0;
    da->capacity = capacity;
    da->destroyer_function = destroyer_function;
    da->copy_function = copy_function;
    da->elems = (TElement *) malloc(capacity * sizeof(TElement));
    if (da->elems == NULL)
        return NULL;

    return da;

}

/// Frees the dynamic array
/// \param da The dynamic array that will be destroyed
void destroy_dynamic_array(DynamicArray *da) {
    if (da == NULL)
        return;

    for (int i = 0; i < da->length; i++) {
        da->destroyer_function(da->elems[i]);
    }
    free(da->elems);
    free(da);
}

/// Resizes the given dynamic array
/// \param da The given dynamic array
void resize_dynamic_array(DynamicArray *da) {
    if (da == NULL)
        return;

    // increasing capacity
    da->capacity = da->capacity * 2;

    //creating a new vector with increased capacity
    TElement *new_elems = (TElement *) malloc(sizeof(TElement) * da->capacity);

    //// copying the elements from the ex-vector to the new one
    for (int i = 0; i < da->capacity / 2; i++) {
        new_elems[i] = da->elems[i];
    }

    // freeing the elements first from the original vector of pointers
    free(da->elems);

    // saving the new created vector of pointers as the new vector
    da->elems = new_elems;
}

/// Creates a copy of the given element and saves it in the d. array
/// \param da The dynamic array given
/// \param elem The element given
void add_element_dynamic_array(DynamicArray *da, TElement elem) {
    if (da == NULL || elem == NULL)
        return;

    //resize if length is at the end of capacity
    if (da->capacity == da->length)
        resize_dynamic_array(da);

    da->elems[da->length] = da->copy_function(elem);
    da->length++;
}

/// Deletes the element at the given index
/// \param da The dynamic array that's going to be worked on
/// \param index The given index
void delete_element_by_index_dynamic_array(DynamicArray *da, int index) {
    if (da == NULL)
        return;
    if (index >= da->length || index < 0)
        return;

    //shifting elements onto it and deleting the element with the given index

    da->destroyer_function(da->elems[index]);
    for (int i = index; i < da->length; i++) {
        da->elems[i] = da->elems[i + 1];
    }
    da->elems[da->length] = NULL;
    da->length--;
}

/// Returns the pointer of the element at the given index
/// \param da The given d array
/// \param index The index given
/// \return A pointer to the element at the given index
TElement get_element_by_index_dynamic_array(DynamicArray *da, int index) {
    if (da == NULL)
        return NULL;
    if (index >= da->length || index < 0)
        return NULL;

    return da->elems[index];
}

/// Returns a pointer to the array of elements
/// \param da The dynamic array
/// \return A pointer to the elements of the dynamic array
TElement *get_all_elements_dynamic_array(DynamicArray *da) {
    if (da == NULL)
        return NULL;

    return da->elems;
}

/// Creates a copy of the given element and saves it at the position indicated by the index, destroying the old value that was on that position
/// \param da The d array
/// \param new_elem The new element for the position index
/// \param index The given index
void update_element_by_index_dynamic_array(DynamicArray *da, TElement new_elem, int index) {
    if (da == NULL || new_elem == NULL)
        return;

    da->destroyer_function(da->elems[index]);
    da->elems[index] = da->copy_function(new_elem);
}

