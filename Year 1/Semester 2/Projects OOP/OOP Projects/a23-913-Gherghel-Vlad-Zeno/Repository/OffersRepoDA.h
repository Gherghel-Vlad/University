//
// Created by Admin on 3/10/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_OFFERSREPODA_H
#define A23_913_GHERGHEL_VLAD_ZENO_OFFERSREPODA_H
#include "../Domain/DynamicArray.h"
#include "../Domain/Offer.h"

typedef struct {
	DynamicArray* da;
} OffersRepo;

/// <summary>
/// Creates a OffersRepo instance
/// </summary>
/// <returns>A pointer to the newly created OffersRepo</returns>
OffersRepo* create_offers_repo();

/// <summary>
/// Initiliasis the data from the repo with some dummy data
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
void initialise_dummy_data_offers_repo(OffersRepo* offersRepo);
/// <summary>
/// Adds an offer to the array of offers
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="elem">The new offer to be added</param>
void add_offer_repo(OffersRepo* offersRepo, Offer* elem);

/// <summary>
/// Deletes an offer from the list of offers
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="index">The position to be deleted</param>
void delete_offer_by_index_offer_repo(OffersRepo* offersRepo, int index);

/// <summary>
/// Updates an offer by knowing its index
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="new_elem">The new element to be used for updating</param>
/// <param name="index">The position of the offer to be updated</param>
void update_offer_by_index_repo(OffersRepo* offersRepo, Offer* new_elem, int index);

/// <summary>
/// Creates a new dynamic array having the same values as the dynamic array from the offer repo
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <returns>A pointer indicating to the newly created dynamic array</returns>
DynamicArray* get_copy_of_all_offers_repo(OffersRepo* offersRepo);

/// <summary>
/// Creates a new dynamic array where all the values are the same as the offers repo but sorted by price
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <returns>A pointer indicating to the newly created dynamic array</returns>
DynamicArray* get_elements_sorted_by_price_asc_repo(OffersRepo* offersRepo);


/// <summary>
/// Frees the memory occupied by the offer repo instance
/// </summary>
/// <param name="offersRepo">The offers repo instance to be freed</param>
void destroy_offers_repo(OffersRepo* offersRepo);

/// <summary>
/// Exercise given at the lab
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="destination">The destination</param>
/// <returns>A pointer to a new dynamic array with the answer</returns>
DynamicArray* get_elements_same_destination_month_asc_repo(OffersRepo* offersRepo, char* destination);

/// <summary>
/// Returns a pointer to the dynamic array of the repo
/// </summary>
/// <param name="offerRepo">The offer repo instance to be worked on</param>
/// <returns>A pointer indicating to the dynamic array of the repo</returns>
DynamicArray* get_dynamic_array_offer_repo(OffersRepo* offerRepo);

/// <summary>
/// Returns a pointer to the element having the given index
/// </summary>
/// <param name="offersRepo">The offer repo to be worked on</param>
/// <param name="index">The index to be searched for</param>
/// <returns>A pointer indicating to the element if it was found, or NULL otherwise</returns>
Offer* get_element_by_index_offer_repo(OffersRepo* offersRepo, int index);

/// <summary>
/// Gets the offer that had the destination and departure date given
/// </summary>
/// <param name="offersRepo">The offer repo instance to be used</param>
/// <param name="destination">The destination to be searched for</param>
/// <param name="departure_date">The departuer date to be searched for</param>
/// <returns>A pointer to the offer that matches, or NULL if it wasnt found</returns>
Offer* get_element_by_destination_and_departure_date_offer_repo(OffersRepo* offersRepo, char* destination, char* departure_date);


/// <summary>
/// Searches for the element in the offer repo
/// </summary>
/// <param name="offersRepo">The isntance of the offer repo to be worked on</param>
/// <param name="elem">The element to be searched for</param>
/// <returns>The index of the elemenet if it was found or -1 if it wasnt </returns>
int get_index_by_element_offers_repo(OffersRepo* offersRepo, Offer* elem);

#endif //A23_913_GHERGHEL_VLAD_ZENO_OFFERSREPODA_H
