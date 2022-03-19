//
// Created by Admin on 3/10/2021.
//

#include "OffersRepoDA.h"
#include "../Domain/Offer.h"
#include "../Domain/DynamicArray.h"
#include <stdlib.h>
#include <string.h>

/// <summary>
/// Creates a OffersRepo instance
/// </summary>
/// <returns>A pointer to the newly created OffersRepo</returns>
OffersRepo* create_offers_repo() {
	OffersRepo* offersRepo = (OffersRepo*)malloc(sizeof(OffersRepo));
	DynamicArray* da = create_dynamic_array(15, destroy_offer, copy_offer);

	if (offersRepo == NULL || da == NULL)
		return NULL;

	offersRepo->da = da;

	return offersRepo;
}

/// <summary>
/// Frees the memory occupied by the offer repo instance
/// </summary>
/// <param name="offersRepo">The offers repo instance to be freed</param>
void destroy_offers_repo(OffersRepo* offersRepo) {
	if (offersRepo == NULL)
		return;
	destroy_dynamic_array(offersRepo->da);
	free(offersRepo);
}

/// <summary>
/// Initiliasis the data from the repo with some dummy data
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
void initialise_dummy_data_offers_repo(OffersRepo* offersRepo) {
	if (offersRepo == NULL)
		return;
	Offer* offer;
	offer = create_offer("seaside", "Miami Beach", "7/9/2021", 500);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("seaside", "Berlin", "4/5/2020", 800.5);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("seaside", "Paris", "10/6/2020", 900.3);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("seaside", "Barselona", "20/3/2021", 1000);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("mountain", "Cluj Napoca", "22/2/2020", 200);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("city break", "Oradea", "4/6/2021", 333.33);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("mountain", "London", "1/4/2021", 555);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("city break", "Tokyo", "26/6/2020", 222.22);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("city break", "Hawai", "21/3/2021", 539);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("mountain", "Budapest", "16/2/2020", 10);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("mountain", "Paris", "16/2/2020", 10);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
	offer = create_offer("mountain", "Paris", "16/11/2020", 10);
	add_element_dynamic_array(offersRepo->da, offer);
	destroy_offer(offer);
}

/// <summary>
/// Adds an offer to the array of offers
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="elem">The new offer to be added</param>
void add_offer_repo(OffersRepo* offersRepo, Offer* elem) {
	if (offersRepo == NULL || elem == NULL)
		return;

	add_element_dynamic_array(offersRepo->da, elem);
}

/// <summary>
/// Returns a pointer to the dynamic array of the repo
/// </summary>
/// <param name="offerRepo">The offer repo instance to be worked on</param>
/// <returns>A pointer indicating to the dynamic array of the repo</returns>
DynamicArray* get_dynamic_array_offer_repo(OffersRepo* offerRepo) {
	if (offerRepo == NULL)
		return NULL;

	return offerRepo->da;
}

/// <summary>
/// Returns a pointer to the element having the given index
/// </summary>
/// <param name="offersRepo">The offer repo to be worked on</param>
/// <param name="index">The index to be searched for</param>
/// <returns>A pointer indicating to the element if it was found, or NULL otherwise</returns>
Offer* get_element_by_index_offer_repo(OffersRepo* offersRepo, int index) {
	if (offersRepo == NULL)
		return NULL;
	return get_element_by_index_dynamic_array(offersRepo->da, index);
}

/// <summary>
/// Deletes an offer from the list of offers
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="index">The position to be deleted</param>
void delete_offer_by_index_offer_repo(OffersRepo* offersRepo, int index) {
	if (offersRepo == NULL)
		return;
	delete_element_by_index_dynamic_array(offersRepo->da, index);
}


/// <summary>
/// Updates an offer by knowing its index
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="new_elem">The new element to be used for updating</param>
/// <param name="index">The position of the offer to be updated</param>
void update_offer_by_index_repo(OffersRepo* offersRepo, Offer* new_elem, int index) {
	if (offersRepo == NULL || new_elem == NULL)
		return;

	update_element_by_index_dynamic_array(offersRepo->da, new_elem, index);
}


/// <summary>
/// Creates a new dynamic array having the same values as the dynamic array from the offer repo
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <returns>A pointer indicating to the newly created dynamic array</returns>
DynamicArray* get_copy_of_all_offers_repo(OffersRepo* offersRepo) {
	DynamicArray* copy_da = create_dynamic_array(offersRepo->da->capacity, destroy_offer, copy_offer);

	Offer* elem, *o;

	for (int i = 0; i < offersRepo->da->length; i++) {
		elem = offersRepo->da->elems[i];
		//TODO Maybe not the best creation
		o = create_offer(elem->type, elem->destination, elem->departure_date, elem->price);
		add_element_dynamic_array(copy_da, o);
		destroy_offer(o);
	}

	return copy_da;
}

/// <summary>
/// Creates a new dynamic array where all the values are the same as the offers repo but sorted by price
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <returns>A pointer indicating to the newly created dynamic array</returns>
DynamicArray* get_elements_sorted_by_price_asc_repo(OffersRepo* offersRepo) {

	DynamicArray* copy_da = get_copy_of_all_offers_repo(offersRepo);
	Offer* aux, *o1, *o2;
	int i, j;
	for (i = 0; i < copy_da->length; i++) {
		for (j = i + 1; j < copy_da->length; j++) {
			o1 = copy_da->elems[i];
			o2 = copy_da->elems[j];
			if (o1->price > o2->price) {
				aux = copy_da->elems[i];
				copy_da->elems[i] = copy_da->elems[j];
				copy_da->elems[j] = aux;
			}
		}
	}

	return copy_da;
}

/// <summary>
/// Exercise given at the lab
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="destination">The destination</param>
/// <returns>A pointer to a new dynamic array with the answer</returns>
DynamicArray* get_elements_same_destination_month_asc_repo(OffersRepo* offersRepo, char* destination) {
	DynamicArray* copy_da = get_copy_of_all_offers_repo(offersRepo);
	Offer* aux;
	Offer* elem;
	int i, j;

	// deletes the offers that dont have the given destination
	for (i = 0; i < copy_da->length; i++) {
		elem = get_element_by_index_dynamic_array(copy_da, i);
		if (strcmp(destination, elem->destination) != 0) {
			delete_element_by_index_dynamic_array(copy_da, i);
			i--;
		}
	}


	int month_first_variable_int, month_second_variable_int;
	char* month_first_variable_char;
	char* month_second_variable_char;
	char month[50];


	for (i = 0; i < copy_da->length; i++) {
		elem = copy_da->elems[i];
		strcpy(month, elem->departure_date);
		month_first_variable_char = strtok(month, "/");
		month_first_variable_char = strtok(NULL, "/");
		month_first_variable_int = atoi(month_first_variable_char);

		for (j = i + 1; j < copy_da->length; j++) {
			elem = copy_da->elems[j];
			strcpy(month, elem->departure_date);
			month_second_variable_char = strtok(month, "/");
			month_second_variable_char = strtok(NULL, "/");
			month_second_variable_int = atoi(month_second_variable_char);
			if (month_first_variable_int > month_second_variable_int) {
				aux = copy_da->elems[i];
				copy_da->elems[i] = copy_da->elems[j];
				copy_da->elems[j] = aux;
			}
		}
	}


	return copy_da;


}

/// <summary>
/// Gets the offer that had the destination and departure date given
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="destination">The destination to be searched for</param>
/// <param name="departure_date">The departuer date to be searched for</param>
/// <returns>A pointer to the offer that matches, or NULL if it wasnt found</returns>
Offer* get_element_by_destination_and_departure_date_offer_repo(OffersRepo* offersRepo, char* destination, char* departure_date) {
	DynamicArray* da = offersRepo->da;
	if (da == NULL || offersRepo == NULL || destination == NULL || departure_date == NULL)
		return NULL;
	Offer* o;
	for (int i = 0; i < da->length; i++)
	{ 
		o = da->elems[i];
		if (strcmp(o->destination, destination) == 0 && strcmp(o->departure_date, departure_date) == 0)
			return da->elems[i];
	}
	return NULL;
}



/// <summary>
/// Searches for the element in the offer repo
/// </summary>
/// <param name="offersRepo">The isntance of the offer repo to be worked on</param>
/// <param name="elem">The element to be searched for</param>
/// <returns>The index of the elemenet if it was found or -1 if it wasnt </returns>
int get_index_by_element_offers_repo(OffersRepo* offersRepo, Offer* elem) {
	DynamicArray* da = offersRepo->da;
	if (da == NULL || elem == NULL || offersRepo == NULL)
		return -1;

	for (int i = 0; i < da->length; i++)
		if (check_offers_equality(elem, da->elems[i]) == 0) {
			return i;
		}

	return -1;
}



//void update_element_by_old_elem_dynamic_array(DynamicArray* da, TElement new_elem, TElement old_elem){
//    if(da == NULL || new_elem == NULL || old_elem == NULL)
//        return;
//    int index = get_index_by_element_dynamic_array(da, old_elem);
//    if(index == -1){
//        return;
//    }
//    destroy_offer(da->elems[index]);
//    da->elems[index] = new_elem;
//}