//
// Created by Admin on 3/9/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_OFFER_H
#define A23_913_GHERGHEL_VLAD_ZENO_OFFER_H

typedef struct {
    char* type;
    char* destination;
    char* departure_date;
    double price;
} Offer;

// creates a new offer instance
Offer* create_offer(char* type,char* destination,char* departure_date,double price);

// saves the type of the given offer pointer in the type char pointer
void get_offer_type(Offer* offer, char* type);

// saves the destination of the given offer pointer in the destination char pointer
void get_offer_destination(Offer* offer, char* destination);

// saves the departure date of the given offer pointer in the departure date char pointer
void get_offer_departure_date(Offer* offer, char* departure_date);

// returns the price of the given offer
double get_offer_price(Offer* offer);

// setters
void set_offer_type(Offer* offer, char* new_type);
void set_offer_destination(Offer* offer, char* new_destination);
void set_offer_departure_date(Offer* offer, char* new_departure_date);
void set_offer_price(Offer* offer, double new_price);

/// Checks if the 2 offers are equal (have all the fields equal).
/// \param o1 First offer
/// \param o2 Second offer
/// \return 0 if they are equal, -1 otherwise
int check_offers_equality(Offer* o1, Offer* o2);

/// Eliberates the memory hold by the offer pointer
/// \param offer The given offer pointer
void destroy_offer(Offer* offer);

/// Creates a new copy of the old offer in the new offer
/// \param old_offer The old offer
Offer* copy_offer(Offer* offer);
#endif //A23_913_GHERGHEL_VLAD_ZENO_OFFER_H
