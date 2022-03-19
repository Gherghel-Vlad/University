//
// Created by Admin on 3/9/2021.
//

#include "tests.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Domain/Offer.h"
#include "../Domain/DynamicArray.h"
#include "../Repository/OffersRepoDA.h"
#include "../Service/OffersService.h"

void test_offer_domain() {

	printf("starting domain tests...\n");

	char type[] = "mountain";
	char destination[] = "Somewhere in the world";
	char departure_date[] = "5/2/2021";
	double price = 299.99;

	// testing create offer
	Offer* offer = create_offer(type, destination, departure_date, price);

	// testing properties
	assert(strcmp(type, offer->type) == 0);
	assert(strcmp(destination, offer->destination) == 0);
	assert(strcmp(departure_date, offer->departure_date) == 0);
	assert(fabs(price - offer->price) < 0.00001);


	char* string = (char*)malloc(sizeof(char) * 50);

	// testing getters
	get_offer_type(offer, string);
	assert(strcmp(string, type) == 0);

	get_offer_destination(offer, string);
	assert(strcmp(string, destination) == 0);

	get_offer_departure_date(offer, string);
	assert(strcmp(string, departure_date) == 0);

	assert(fabs(get_offer_price(offer) - price) < 0.00001);


	char new_type[] = "new mountain";
	char new_destination[] = " new Somewhere in the world";
	char new_departure_date[] = "15/2/2021";
	double new_price = 420.69;

	//testing setters
	set_offer_type(offer, new_type);
	get_offer_type(offer, string);
	assert(strcmp(string, new_type) == 0);

	set_offer_destination(offer, new_destination);
	get_offer_destination(offer, string);
	assert(strcmp(string, new_destination) == 0);

	set_offer_departure_date(offer, new_departure_date);
	get_offer_departure_date(offer, string);
	assert(strcmp(string, new_departure_date) == 0);

	set_offer_price(offer, new_price);
	assert(fabs(get_offer_price(offer) - new_price) < 0.00001);

	// testing equality checking
	Offer* o1 = create_offer("asd", "gdfsf", "gregr", 100);
	Offer* o2 = create_offer("asd", "gdfsf", "gregr", 100);
	Offer* o3 = create_offer("asdf", "gdfsf", "gregr", 100);

	assert(check_offers_equality(o1, o2) == 0);
	assert(check_offers_equality(o1, o3) == -1);

	// testing copy_offer
	Offer* o4 = copy_offer(o1);

	assert(check_offers_equality(o1, o4) == 0);

	//destroying the elements
	destroy_offer(offer);
	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);
	destroy_offer(o4);
	free(string);

	printf("stopped domain tests...\n");
}

void test_dynamic_array() {
	printf("starting dynamic array testing...\n");
	DynamicArray* da = create_dynamic_array(2, destroy_offer, copy_offer);
	Offer* o1 = create_offer("seaside", "somewhere far away", "1/10/2020", 200.2);
	Offer* o2 = create_offer("mountain", "somewhere far away, in another galaxy", "12/10/2022", 222.2);
	Offer* o3 = create_offer("mountain", "somewhere far away, in another galaxy x2", "12/11/2022", 232.2);

	// testing adding
	add_element_dynamic_array(da, o1);
	assert(check_offers_equality(da->elems[0], o1) == 0);

	add_element_dynamic_array(da, o2);
	assert(check_offers_equality(da->elems[1], o2) == 0);

	add_element_dynamic_array(da, o3);
	assert(check_offers_equality(da->elems[2], o3) == 0);
	assert(da->capacity == 4);

	// testing get element by index
	assert(check_offers_equality(get_element_by_index_dynamic_array(da, 2), o3) == 0);

	// testing get all elements
	assert(da->elems == get_all_elements_dynamic_array(da));

	// testing update
	update_element_by_index_dynamic_array(da, o2, 2);

	assert(check_offers_equality(get_element_by_index_dynamic_array(da, 2), o2) == 0);

	// testing deleting
	delete_element_by_index_dynamic_array(da, 0);
	assert(check_offers_equality(da->elems[0], o2) == 0);

	destroy_dynamic_array(da);
	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);
	printf("stopped dynamic array testing...\n");
}

void test_offers_repo() {
	printf("starting repo testing...\n");

	OffersRepo* offersRepo = create_offers_repo();

	//testing initialise dummy data
	initialise_dummy_data_offers_repo(offersRepo);
	assert(offersRepo->da->length == 12);

	//testing adding
	Offer* o1 = create_offer("mountain", "Hawai", "12/4/2020", 120);
	add_offer_repo(offersRepo, o1);
	assert(offersRepo->da->length == 13);
	assert(check_offers_equality(o1, get_element_by_index_dynamic_array(get_dynamic_array_offer_repo(offersRepo), 12) == 0));

	//testing deleting
	Offer* o2 = copy_offer(get_element_by_index_offer_repo(offersRepo, 3));
	delete_offer_by_index_offer_repo(offersRepo, 3);
	assert(offersRepo->da->length == 12);
	assert(check_offers_equality(o2, get_element_by_index_offer_repo(offersRepo, 3)) != 0);

	// testing update
	Offer* o3 = create_offer("mountain", "Hawa32i", "15/4/2020", 1250);
	Offer* o4 = create_offer("mountain", "Haw45ai", "12/4/2020", 1240);
	update_offer_by_index_repo(offersRepo, o3, 5);
	assert(check_offers_equality(o3, get_element_by_index_offer_repo(offersRepo, 5)) == 0);
	update_offer_by_index_repo(offersRepo, o4, 6);
	assert(check_offers_equality(o4, get_element_by_index_offer_repo(offersRepo, 6)) == 0);

	// testing getters
	Offer* o5 = create_offer("seaside", "Paris", "10/6/2020", 900.3);
	assert(check_offers_equality(get_element_by_destination_and_departure_date_offer_repo(offersRepo, "Paris", "10/6/2020"), o5) == 0);
	assert(get_index_by_element_offers_repo(offersRepo, o5) == 2);


	//testing destroying
	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);
	destroy_offer(o4);
	destroy_offer(o5);
	destroy_offers_repo(offersRepo);

	printf("stoping repo testing...\n");

}

void test_offers_service() {
	printf("starting offers service testing...\n");


	OffersService* offersService = create_offers_service();

	// testing adding
	Offer* o1 = create_offer("mountain", "Hawai", "12/5/2021", 1234);
	add_element_offers_service(offersService, o1);
	assert(offersService->offersRepo->da->length == 1);
	assert(check_offers_equality(get_element_by_index_offer_repo(offersService->offersRepo, 0), o1)==0);
	

	Offer* o2 = create_offer("seaside", "Paris", "17/5/2021", 12434);
	Offer* o3 = create_offer("mountain", "australia", "15/5/2021", 1334);
	add_element_offers_service(offersService, o2);
	add_element_offers_service(offersService, o3);

	// testing delete
	delete_element_by_destination_and_departure_date_offers_service(offersService, "Paris", "17/5/2021");
	assert(offersService->offersRepo->da->length == 2);
	assert(check_offers_equality(get_element_by_index_offer_repo(offersService->offersRepo, 1), o3)==0);

	add_element_offers_service(offersService, o2);
	delete_element_by_index_offers_service(offersService, 1);
	assert(offersService->offersRepo->da->length == 2);
	assert(check_offers_equality(get_element_by_index_offer_repo(offersService->offersRepo, 1), o2)==0);

	// testing update
	update_element_by_destination_and_departure_date_offers_service(offersService, o3, "Paris", "17/5/2021");
	assert(check_offers_equality(get_element_by_index_offer_repo(offersService->offersRepo, 1), o3) == 0);

	update_element_by_index_offers_service(offersService, o2, 1);
	assert(check_offers_equality(get_element_by_index_offer_repo(offersService->offersRepo, 1), o2) == 0);

	
	//testing destroying
	destroy_offers_service(offersService);
	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);

	printf("stoping offers service testing...\n");

}


void test_all() {
	test_offer_domain();
	test_dynamic_array();
	test_offers_repo();
	test_offers_service();
}

