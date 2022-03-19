//
// Created by Admin on 3/9/2021.
//

#include "Offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/// Creates a pointer to a struct of type Offer with the given type, destination, departure date and price
/// \param type The given type (seaside, mountain or city break) (char vector)
/// \param destination The given destination (char vector)
/// \param departure_date The given date (dd/mm/yyyy) (char vector)
/// \param price Given price (double)
/// \return A pointer indicating to a new Offer pointer
Offer *create_offer(char *type, char *destination, char *departure_date, double price) {
    Offer *offer = (Offer *) malloc(sizeof(Offer));

    offer->type = (char *) malloc(sizeof(char) * strlen(type) + 1);
    offer->destination = (char *) malloc(sizeof(char) * strlen(destination) + 1);
    offer->departure_date = (char *) malloc(sizeof(char) * strlen(departure_date) + 1);

    // checking that the memory was allocated successfully
    if (offer->type == NULL || offer->destination == NULL || offer->departure_date == NULL)
        return NULL;

    strcpy(offer->type, type);
    strcpy(offer->destination, destination);
    strcpy(offer->departure_date, departure_date);

    offer->price = price;

    return offer;
}

/// Saves the type of the given Offer in the given char pointer type
/// \param offer The offer given (Offer pointer)
/// \param type The given type (char pointer)
void get_offer_type(Offer *offer, char *type) {
    if (offer == NULL) {
        return;
    }
    strcpy(type, offer->type);
}

/// Saves the destination of the given Offer in the given char pointer destination
/// \param offer The offer given (Offer pointer)
/// \param destination The given destination (char pointer)
void get_offer_destination(Offer *offer, char *destination) {
    if (offer == NULL) {
        return;
    }
    strcpy(destination, offer->destination);
}

/// Saves the departure date of the given Offer in the given char pointer departure_date
/// \param offer The offer given (Offer object)
/// \param departure_date The given departure date (char pointer)
void get_offer_departure_date(Offer *offer, char *departure_date) {
    if (offer == NULL) {
        return;
    }
    strcpy(departure_date, offer->departure_date);
}

/// Returns the price of a given Offer
/// \param offer The given offer (Offer pointer)
/// \return
double get_offer_price(Offer *offer) {
    if (offer == NULL) {
        return 0;
    }
    return offer->price;
}

/// Sets the offer's type as the new given type
/// \param offer The offer pointer
/// \param new_type The new type
void set_offer_type(Offer *offer, char *new_type) {
    if (offer == NULL) {
        return;
    }
    free(offer->type);
    offer->type = (char *) malloc(sizeof(char) * strlen(new_type) + 1);
    if (offer->type == NULL)
        return;
    strcpy(offer->type, new_type);
}

/// Sets the offer's destination as the new given destination
/// \param offer The offer pointer
/// \param new_destination The new destination
void set_offer_destination(Offer *offer, char *new_destination) {
    if (offer == NULL) {
        return;
    }
    free(offer->destination);
    offer->destination = (char *) malloc(sizeof(char) * strlen(new_destination) + 1);
    if (offer->destination == NULL)
        return;
    strcpy(offer->destination, new_destination);
}

/// Sets the offer's departure date as the new departure date
/// \param offer The given offer pointer
/// \param new_departure_date The new departure date
void set_offer_departure_date(Offer *offer, char *new_departure_date) {
    if (offer == NULL) {
        return;
    }
    free(offer->departure_date);
    offer->departure_date = (char *) malloc(sizeof(char) * strlen(new_departure_date) + 1);

    if (offer->departure_date == NULL)
        return;

    strcpy(offer->departure_date, new_departure_date);
}

/// Sets the price of the given offer pointer with the new price
/// \param offer Given offer pointer
/// \param new_price Given new price (double)
void set_offer_price(Offer *offer, double new_price) {
    if (offer == NULL) {
        return;
    }

    offer->price = new_price;
}

/// Checks if the 2 offers are equal (have all the fields equal).
/// \param o1 First offer
/// \param o2 Second offer
/// \return 0 if they are equal, -1 otherwise
int check_offers_equality(Offer *o1, Offer *o2) {
    if (o1 == NULL || o2 == NULL)
        return -1;
    if (strcmp(o1->type, o2->type) == 0 && strcmp(o1->destination, o2->destination) == 0 &&
        strcmp(o1->departure_date, o2->departure_date) == 0 && fabs(o1->price - o2->price) < 0.0001)
        return 0;
    return -1;

}

/// Eliberates the memory hold by the offer pointer
/// \param offer The given offer pointer
void destroy_offer(Offer *offer) {
    if (offer == NULL) {
        return;
    }
    free(offer->type);
    free(offer->destination);
    free(offer->departure_date);
    free(offer);
}
/// Creates a new copy of the offer and returns a pointer to it
/// \param offer The offer to be copied
Offer* copy_offer(Offer* offer){
    if (offer==NULL)
        return NULL;

    return create_offer(offer->type, offer->destination, offer->departure_date, offer->price);
}

