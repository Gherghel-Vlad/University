//
// Created by Admin on 3/17/2021.
//

#include "OfferValidators.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/// <summary>
/// Checks the type of an offer it its correct
/// </summary>
/// <param name="type">The type string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_type_validator(char* type) {
	if (type == NULL)
		return ERROR_INVALID_TYPE;
	if (strcmp(type, "mountain") == 0 || strcmp(type, "city break") == 0 || strcmp(type, "seaside") == 0)
		return 1;
	return ERROR_INVALID_TYPE;
}

/// <summary>
/// Checks the type of an offer it its correct
/// </summary>
/// <param name="destination">The destination string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_destination_validator(char* destination) {
	if (destination == NULL)
		return ERROR_INVALID_DESTINATION;
	return 1;
}

/// <summary>
/// Checks the departure date of an offer it its correct
/// </summary>
/// <param name="departure_date">The departure date string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_departure_date_validator(char* departure_date) {
	if (departure_date == NULL)
		return ERROR_INVALID_DEPARTURE_DATE;
	int nr, index = 0;
	char date[101];
	strncpy(date, departure_date, 100);
	date[100] = '\0';
	char* p;
	p = strtok(date, "/");

	while (p) {
		nr = atoi(p);
		if (nr == 0)
			return ERROR_INVALID_DEPARTURE_DATE;

		switch (index)
		{
		case 0:
			if (nr > 31)
				return ERROR_INVALID_DEPARTURE_DATE;
			break;
		case 1:
			if (nr > 12)
				return ERROR_INVALID_DEPARTURE_DATE;
			break;
		case 2:
			break;
		default:
			return ERROR_INVALID_DEPARTURE_DATE;
			break;
		}
		index++;
		p = strtok(NULL, "/");
	}
	return 1;
}

/// <summary>
/// Checks the price  of an offer it its correct
/// </summary>
/// <param name="price">The price </param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_price_validator(double price)
{
	return 1;
}

/// <summary>
/// Checks the offer it its correct
/// </summary>
/// <param name="offer">The offer pointer</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_validator(Offer* offer) {

	if (check_offer_type_validator(offer->type) != 1 || check_offer_destination_validator(offer->destination) != 1 || check_offer_departure_date_validator(offer->departure_date) != 1 || check_offer_price_validator(offer->price) != 1)
		return ERROR_INVALID_OFFER;
	return 1;
}

