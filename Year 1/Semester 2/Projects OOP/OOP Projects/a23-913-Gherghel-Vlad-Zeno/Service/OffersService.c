//
// Created by Admin on 3/10/2021.
//

#include "OffersService.h"
#include "../Domain/Offer.h"
#include "../Validators/OfferValidators.h"
#include <stdlib.h>
#include <string.h>

/// <summary>
/// Creates an isntance of the offer service
/// </summary>
/// <returns>A pointer to the newly created instance of the offer service</returns>
OffersService* create_offers_service() {
	OffersService* offersService = (OffersService*)malloc(sizeof(OffersService));
	offersService->ur = create_undo_redo();
	offersService->offersRepo = create_offers_repo();
	return offersService;
}



/// <summary>
/// Frees the offers service
/// </summary>
/// <param name="offersService">The instance of the offers service</param>
void destroy_offers_service(OffersService* offersService) {
	if (offersService == NULL)
		return;

	destroy_offers_repo(offersService->offersRepo);
	destroy_undo_redo(offersService->ur);
	free(offersService);
}

/// <summary>
/// Adds an new offer to the elements
/// </summary>
/// <param name="offersService">The offer service instance</param>
/// <param name="elem">The new offer to be added</param>
/// <returns>A number representing an error</returns>
int add_element_offers_service(OffersService* offersService, Offer* elem) {
	if (offersService == NULL || elem == NULL)
		return -1;
	if (check_offer_validator(elem) % ERROR_INVALID_OFFER == 0)
		return ERROR_INVALID_OFFER;
	if (get_index_by_element_offers_repo(offersService->offersRepo, elem) != -1)
		return ERROR_INVALID_INDEX;


	add_list_undo_redo(offersService->ur, offersService->offersRepo->da);
	add_offer_repo(offersService->offersRepo, elem);
}

/// <summary>
/// Deletes the offer that has the given index
/// </summary>
/// <param name="offersService">The offer service instance</param>
/// <param name="index">The index of the offer to be deleted</param>
/// <returns>A number representing an error</returns>
int delete_element_by_index_offers_service(OffersService* offersService, int index) {
	if (offersService == NULL)
		return -1;

	if (get_element_by_index_offer_repo(offersService->offersRepo, index) == NULL)
		return ERROR_INVALID_INDEX;

	add_list_undo_redo(offersService->ur, offersService->offersRepo->da);
	delete_offer_by_index_offer_repo(offersService->offersRepo, index);
}

/// <summary>
/// Deletes the element that has the given destination and departure date 
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <param name="destination">The destination to search for</param>
/// <param name="departure_date">The departure date to search for</param>
/// <returns>A number representing an error</returns>
int delete_element_by_destination_and_departure_date_offers_service(OffersService* offersService, char* destination, char* departure_date) {
	if (offersService == NULL || destination == NULL || departure_date == NULL)
		return -1;
	if (check_offer_destination_validator(destination) % ERROR_INVALID_DESTINATION == 0)
		return ERROR_INVALID_DESTINATION;
	if (check_offer_departure_date_validator(departure_date) % ERROR_INVALID_DEPARTURE_DATE == 0)
		return ERROR_INVALID_DEPARTURE_DATE;
	if (get_element_by_destination_and_departure_date_offer_repo(offersService->offersRepo, destination, departure_date) == NULL)
		return ERROR_OFFER_DOESNT_EXIST;

	add_list_undo_redo(offersService->ur, offersService->offersRepo->da);
	delete_offer_by_index_offer_repo(offersService->offersRepo, get_index_by_element_offers_repo(offersService->offersRepo, get_element_by_destination_and_departure_date_offer_repo(offersService->offersRepo, destination, departure_date)));
}

/// <summary>
/// Updates the offer on the position of the index with the given new offer
/// </summary>
/// <param name="offersService">The isntance of the offers service</param>
/// <param name="new_elem">The new offer</param>
/// <param name="index">The index of the element</param>
/// <returns>A number representing an error</returns>
int update_element_by_index_offers_service(OffersService* offersService, Offer* new_elem, int index) {
	if (offersService == NULL || new_elem == NULL)
		return -1;
	if (get_element_by_index_offer_repo(offersService->offersRepo, index) == NULL)
		return ERROR_INVALID_INDEX;
	if (check_offer_validator(new_elem) % ERROR_INVALID_OFFER == 0)
		return ERROR_INVALID_OFFER;

	add_list_undo_redo(offersService->ur, offersService->offersRepo->da);
	update_offer_by_index_repo(offersService->offersRepo, new_elem, index);
}

/// <summary>
/// Updates the element which has the destination and departure date given
/// </summary>
/// <param name="offersService">The instance of teh offers service</param>
/// <param name="new_elem">The enw element that will be used to update the old one</param>
/// <param name="destination">The destination to be searched for</param>
/// <param name="departure_date">The departure date to be searched for</param>
/// <returns>A number representing an error</returns>
int update_element_by_destination_and_departure_date_offers_service(OffersService* offersService, Offer* new_elem, char* destination, char* departure_date) {
	if (offersService == NULL || new_elem == NULL || destination == NULL || departure_date == NULL)
		return -1;
	if (check_offer_destination_validator(destination) % ERROR_INVALID_DESTINATION == 0)
		return ERROR_INVALID_DESTINATION;
	if (check_offer_departure_date_validator(departure_date) % ERROR_INVALID_DEPARTURE_DATE == 0)
		return ERROR_INVALID_DEPARTURE_DATE;
	if (check_offer_validator(new_elem) % ERROR_INVALID_OFFER == 0)
		return ERROR_INVALID_OFFER;
	if (get_element_by_destination_and_departure_date_offer_repo(offersService->offersRepo, destination, departure_date) == NULL)
		return ERROR_OFFER_DOESNT_EXIST;

	add_list_undo_redo(offersService->ur, offersService->offersRepo->da);
	update_offer_by_index_repo(offersService->offersRepo, new_elem, get_index_by_element_offers_repo(offersService->offersRepo, get_element_by_destination_and_departure_date_offer_repo(offersService->offersRepo, destination, departure_date)));
}




/// <summary>
/// Creates a deep copy of the dynamic array and returns the pointer to it
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <returns>A pointer indicating the newly deep cope of the dynamic array</returns>
DynamicArray* get_all_elements_offers_service(OffersService* offersService) {
	if (offersService == NULL)
	{
		return NULL;
	}

	return get_copy_of_all_offers_repo(offersService->offersRepo);
}

/// <summary>
/// Gets all the elements into a new dynamic array that has the substring in their destination sorted by price ascending
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <param name="substring">The substring to be searched in destination</param>
/// <returns>A pointer to a newly deep copy dynamic array</returns>
DynamicArray* get_all_elements_with_dest_substring_and_sorted_by_price_asc_offers_service(OffersService* offersService, char* substring) {
	if (offersService == NULL || substring == NULL)
		return NULL;

	DynamicArray* copy_da = get_elements_sorted_by_price_asc_repo(offersService->offersRepo);
	DynamicArray* new_substring_da = create_dynamic_array(copy_da->capacity, destroy_offer, copy_offer);
	Offer* elem, * o1, * o2;
	for (int i = 0; i < copy_da->length; i++) {
		o1 = copy_da->elems[i];
		if (strstr(o1->destination, substring) != NULL) {
			elem = copy_da->elems[i];
			o2 = create_offer(elem->type, elem->destination, elem->departure_date, elem->price);
			//TODO maybe not the best implementation here too
			add_element_dynamic_array(new_substring_da, o2);
			destroy_offer(o2);
		}
	}

	destroy_dynamic_array(copy_da);
	return new_substring_da;
}

/// <summary>
/// Exercise given at the lab
/// </summary>
/// <param name="offersService"></param>
/// <param name="destination"></param>
/// <returns></returns>
DynamicArray* get_elements_same_destination_month_asc_service(OffersService* offersService, char* destination) {
	if (destination == NULL || offersService == NULL) {
		return NULL;
	}

	return get_elements_same_destination_month_asc_repo(offersService->offersRepo, destination);
}

/// <summary>
/// Gets the element at the specified index
/// </summary>
/// <param name="offersService">Instance</param>
/// <param name="index">Position</param>
/// <returns>A pointer to the element of the specified index, or null if it s a wrong index</returns>
Offer* get_element_by_index_offer_service(OffersService* offersService, int index) {
	if (offersService == NULL)
		return NULL;

	return get_element_by_index_offer_repo(offersService->offersRepo, index);
}

/// <summary>
/// Gets the index of the element from the array
/// </summary>
/// <param name="offersService">Instance</param>
/// <param name="offer">The offer to be searched</param>
/// <returns>The index if the element was found, -1 otherwise</returns>
int get_index_by_element_offer_service(OffersService* offersService, Offer* offer) {
	if (offersService == NULL || offer == NULL)
		return NULL;

	return  get_index_by_element_offers_repo(offersService->offersRepo, offer);
}

DynamicArray* get_all_offers_of_same_type_bigger_than_a_date_offer_service(OffersService* offersService, char* type, char* departure_date) {
	if (check_offer_departure_date_validator(departure_date) != 1)
		return ERROR_INVALID_DEPARTURE_DATE;
	if (check_offer_type_validator(type) != 1)
		return ERROR_INVALID_TYPE;

	DynamicArray* new_da = create_dynamic_array(offersService->offersRepo->da->length, destroy_offer, copy_offer);
	DynamicArray* da = offersService->offersRepo->da;
	Offer* o;
	char* p, date[50];
	int day=-1, month=-1, year=-1, day1, month1, year1;

	strcpy(date, departure_date);

	p = strtok(date, "/");

	while (p) {
		if (day == -1)
			day = atoi(p);
		else {
			if (month == -1)
				month = atoi(p);
			else
				year = atoi(p);
		}
		p = strtok(NULL, "/");
	}



	for (int i = 0; i < da->length; i++)
	{
		o = da->elems[i];
		if (strcmp(type, o->type) == 0) {
			strcpy(date, o->departure_date);
			day1 = month1 = year1 = -1;
			p= strtok(date, "/");

			while (p) {
				if (day1 == -1)
					day1 = atoi(p);
				else {
					if (month1 == -1)
						month1 = atoi(p);
					else
						year1 = atoi(p);
				}
				p = strtok(NULL, "/");
			}

			if (year1 > year)
				add_element_dynamic_array(new_da, o);
			else {
				if (year1 == year) {
					if (month1 > month) {
						add_element_dynamic_array(new_da, o);
					}
					else {
						if (month1 == month) {
							if(day1>day)
								add_element_dynamic_array(new_da, o);
						}
					}
				}
			}



		}




	}

	return new_da;

}
