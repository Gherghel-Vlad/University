//
// Created by Admin on 3/10/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_OFFERSSERVICE_H
#define A23_913_GHERGHEL_VLAD_ZENO_OFFERSSERVICE_H

#include "../Repository/OffersRepoDA.h"
#include "../UndoRedo/UndoRedo.h"

typedef struct {
    OffersRepo* offersRepo;
    UndoRedo* ur;
} OffersService;

/// <summary>
/// Creates an isntance of the offer service
/// </summary>
/// <returns>A pointer to the newly created instance of the offer service</returns>
OffersService* create_offers_service();

/// <summary>
/// Adds an new offer to the elements
/// </summary>
/// <param name="offersService">The offer service instance</param>
/// <param name="elem">The new offer to be added</param>
/// <returns>A number representing an error</returns>
int add_element_offers_service(OffersService* offersService, Offer* elem);

/// <summary>
/// Deletes the offer that has the given index
/// </summary>
/// <param name="offersService">The offer service instance</param>
/// <param name="index">The index of the offer to be deleted</param>
/// <returns>A number representing an error</returns>
int delete_element_by_index_offers_service(OffersService* offersService, int index);

/// <summary>
/// Deletes the element that has the given destination and departure date 
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <param name="destination">The destination to search for</param>
/// <param name="departure_date">The departure date to search for</param>
/// <returns>A number representing an error</returns>
int delete_element_by_destination_and_departure_date_offers_service(OffersService* offersService, char* destination, char* departure_date);

/// <summary>
/// Updates the offer on the position of the index with the given new offer
/// </summary>
/// <param name="offersService">The isntance of the offers service</param>
/// <param name="new_elem">The new offer</param>
/// <param name="index">The index of the element</param
/// <returns>A number representing an error</returns>
int update_element_by_index_offers_service(OffersService* offersService, Offer* new_elem, int index);

/// <summary>
/// Updates the element which has the destination and departure date given
/// </summary>
/// <param name="offersService">The instance of teh offers service</param>
/// <param name="new_elem">The enw element that will be used to update the old one</param>
/// <param name="destination">The destination to be searched for</param>
/// <param name="departure_date">The departure date to be searched for</param>
/// <returns>A number representing an error</returns>
int update_element_by_destination_and_departure_date_offers_service(OffersService* offersService, Offer* new_elem, char* destination, char* departure_date);

/// <summary>
/// Creates a deep copy of the dynamic array and returns the pointer to it
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <returns>A pointer indicating the newly deep cope of the dynamic array</returns>
DynamicArray* get_all_elements_offers_service(OffersService* offersService);

/// <summary>
/// Gets all the elements into a new dynamic array that has the substring in their destination sorted by price ascending
/// </summary>
/// <param name="offersService">The instance of the offer service</param>
/// <param name="substring">The substring to be searched in destination</param>
/// <returns>A pointer to a newly deep copy dynamic array</returns>
DynamicArray* get_all_elements_with_dest_substring_and_sorted_by_price_asc_offers_service(OffersService* offersService, char* substring);


/// <summary>
/// Frees the offers service
/// </summary>
/// <param name="offersService">The instance of the offers service</param>
void destroy_offers_service(OffersService* offersService);

/// <summary>
/// Exercise given at the lab
/// </summary>
/// <param name="offersService"></param>
/// <param name="destination"></param>
/// <returns></returns>
DynamicArray* get_elements_same_destination_month_asc_service(OffersService* offersService, char* destination);


/// <summary>
/// Gets the index of the element from the array
/// </summary>
/// <param name="offersService">Instance</param>
/// <param name="offer">The offer to be searched</param>
/// <returns>The index if the element was found, -1 otherwise</returns>
int get_index_by_element_offer_service(OffersService* offersService, Offer* offer);

/// <summary>
/// Gets the element at the specified index
/// </summary>
/// <param name="offersService">Instance</param>
/// <param name="index">Position</param>
/// <returns>A pointer to the element of the specified index, or null if it s a wrong index</returns>
Offer* get_element_by_index_offer_service(OffersService* offersService, int index);

/// <summary>
/// Gets the exercise c
/// </summary>
/// <param name="offersService"></param>
/// <param name="type"></param>
/// <param name="departure_date"></param>
/// <returns></returns>
DynamicArray* get_all_offers_of_same_type_bigger_than_a_date_offer_service(OffersService* offersService, char* type, char* departure_date);

#endif //A23_913_GHERGHEL_VLAD_ZENO_OFFERSSERVICE_H
