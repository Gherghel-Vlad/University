//
// Created by Admin on 3/17/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_OFFERVALIDATORS_H
#define A23_913_GHERGHEL_VLAD_ZENO_OFFERVALIDATORS_H
// Erorr list
#define ERROR_INVALID_TYPE 2
#define ERROR_INVALID_DESTINATION 3
#define ERROR_INVALID_DEPARTURE_DATE 5
#define ERROR_INVALID_PRICE 7
#define ERROR_INVALID_OFFER 11
#define ERROR_OFFER_ALREADY_EXISTS 13
#define ERROR_INVALID_INDEX 17
#define ERROR_OFFER_DOESNT_EXIST 19
#include "../Domain/Offer.h"

/// <summary>
/// Checks the type of an offer it its correct
/// </summary>
/// <param name="type">The type string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_type_validator(char* type);

/// <summary>
/// Checks the type of an offer it its correct
/// </summary>
/// <param name="destination">The destination string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_destination_validator(char* destination);

/// <summary>
/// Checks the departure date of an offer it its correct
/// </summary>
/// <param name="departure_date">The departure date string</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_departure_date_validator(char* departure_date);

/// <summary>
/// Checks the price  of an offer it its correct
/// </summary>
/// <param name="price">The price </param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_price_validator(double price);

/// <summary>
/// Checks the offer it its correct
/// </summary>
/// <param name="offer">The offer pointer</param>
/// <returns>An error, or one is its alrigth</returns>
int check_offer_validator(Offer* offer);

#endif //A23_913_GHERGHEL_VLAD_ZENO_OFFERVALIDATORS_H
