//
// Created by Admin on 3/9/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_DYNAMICARRAY_H
#define A23_913_GHERGHEL_VLAD_ZENO_DYNAMICARRAY_H


typedef void *TElement;

typedef struct {
    TElement *elems;
    int length;
    int capacity;

    void (*destroyer_function)(void *);

    void* (*copy_function)(void *);

} DynamicArray;

/// Creates a dynamic array with the given capacity, which will use destroyer_function to destroy elements and copy_function to copy them
/// \param capacity The initial capacity of the dynamic vector
/// \param destroyer The function that frees an element from this array
/// \param copy_function The function that returns a new pointer to a new element created using an already existing element
/// \return A pointer to the new dynamic array created
DynamicArray *create_dynamic_array(int capacity, void *destroyer, void *copy_function);

/// Frees the dynamic array
/// \param da The dynamic array that will be destroyed
void destroy_dynamic_array(DynamicArray *da);

/// Creates a copy of the given element and saves it in the d. array
/// \param da The dynamic array given
/// \param elem The element given
void add_element_dynamic_array(DynamicArray *da, TElement elem);

/// Deletes the element at the given index
/// \param da The dynamic array that's going to be worked on
/// \param index The given index
void delete_element_by_index_dynamic_array(DynamicArray *da, int index);

/// Returns the pointer of the element at the given index
/// \param da The given d array
/// \param index The index given
/// \return A pointer to the element at the given index
TElement get_element_by_index_dynamic_array(DynamicArray *da, int index);

/// Returns a pointer to the array of elements
/// \param da The dynamic array
/// \return A pointer to the elements of the dynamic array
TElement *get_all_elements_dynamic_array(DynamicArray *da);

/// Creates a copy of the given element and saves it at the position indicated by the index, destroying the old value that was on that position
/// \param da The d array
/// \param new_elem The new element for the position index
/// \param index The given index
void update_element_by_index_dynamic_array(DynamicArray *da, TElement new_elem, int index);


#endif //A23_913_GHERGHEL_VLAD_ZENO_DYNAMICARRAY_H
