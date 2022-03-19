//
// Created by Admin on 3/10/2021.
//

#include "ui.h"
#include "../Validators/OfferValidators.h"
#include "../UndoRedo/UndoRedo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

UI *create_ui() {
    UI *ui = (UI *) malloc(sizeof(UI *));
    ui->offersService = create_offers_service();
    return ui;
}

void destroy_ui(UI *ui) {
    destroy_offers_service(ui->offersService);
    free(ui);
}


void print_menu() {
    printf("\nMenu:\n");
    printf("1 Add new offer.\n");
    printf("2 Delete offer.\n");
    printf("3 Update offer.\n");
    printf("4 Show all offers.\n");
    printf("5 Show all offers with a given substring in destination, ordered asc by price.\n");
    printf("6 Print all destinations with month in ascending order.\n");
    printf("7 Print all offers with the same type and bigger than a date.\n");
    printf("8 Undo.\n");
    printf("9 Redo.\n");
    printf("0 Exit.\n\n");
}

void read_variables(char *type, char *destination, char *departure_date, double *price) {
    printf("Give type (seaside, mountain or city break): ");
    fgets(type, 50, stdin);
    type[strlen(type)-1] = '\0';
    printf("Give destination: ");
    fgets(destination, 256, stdin);
    destination[strlen(destination)-1] = '\0';
    printf("Give departure date (format: dd/mm/yyyy): ");
    fgets(departure_date, 50, stdin);
    departure_date[strlen(departure_date)-1] = '\0';
    printf("Give price (double): ");
    scanf("%lf", price);

}

void check_errors(UI* ui, int error_number) {
    switch (error_number)
    {
    case -1:
        printf("Invalid input.\n");
        break;
    case ERROR_INVALID_DEPARTURE_DATE:
        printf("Invalid departure date.\n");
        break;
    case ERROR_INVALID_DESTINATION:
        printf("Invalid destination.\n");
        break;
    case ERROR_INVALID_INDEX:
        printf("Invalid index.\n");
        break;
    case ERROR_INVALID_OFFER:
        printf("Invalid offer.\n");
        break;
    case ERROR_INVALID_PRICE:
        printf("Invalid price.\n");
        break;
    case ERROR_INVALID_TYPE:
        printf("Invalid type.\n");
        break;
    case ERROR_OFFER_ALREADY_EXISTS:
        printf("Invalid offer, it already exists.\n");
        break;
    case ERROR_OFFER_DOESNT_EXIST:
        printf("Invalid input, offer doesn't exist.\n");
        break;
    default:
        printf("Command ran successfully!\n");
        break;
    }



}

void add_offer_ui(UI *ui) {
    char type[50], destination[256], departure_date[50];
    double price = 0;
    read_variables(type, destination, departure_date, &price);
    Offer *offer = create_offer(type, destination, departure_date, price);
    check_errors(ui, add_element_offers_service(ui->offersService, offer));

    destroy_offer(offer);
}

void delete_offer_ui(UI *ui) {
    int done = 0;
    char command[10], destination[256], departure_date[50];
    int index, number_command;
    Offer *offer;

    while (done == 0) {
        printf("1 By index.\n 2 By destination and departure date.\n 0 Exit.\n");
        done = 1;
        fseek(stdin, 0, SEEK_END);
        printf("Give command: ");
        fgets(command, 10, stdin);
        command[strlen(command) - 1] = '\0';
        number_command = atoi(command);

        switch (number_command) {
            case 1:
                printf("Give index: ");
                scanf("%d", &index);
                check_errors(ui, delete_element_by_index_offers_service(ui->offersService, index));
                break;
            case 2:
                printf("Give destination: ");
                fgets(destination, 256, stdin);
                destination[strlen(destination)-1] = '\0';
                printf("Give departure date (format: dd/mm/yyyy): ");
                fgets(departure_date, 50, stdin);
                departure_date[strlen(departure_date)-1] = '\0';
                
                check_errors(ui, delete_element_by_destination_and_departure_date_offers_service(ui->offersService, destination, departure_date));
                break;
            case 0:
                done = 1;
                return;
                break;
            default:
                printf("Wrong command.\n");
        }


    }
}

void update_offer_UI(UI *ui) {
    int done = 0;
    char command[10], destination[256], departure_date[50];
    int index, number_command;
    Offer *offer, *new_offer;
    char type[50], departure_date_for_search[50], destination_for_search[256];
    double price = 0;

    while (done == 0) {
        printf("1 By index.\n 2 By destination and departure date.\n 0 Exit.\n");
        done = 1;
        fseek(stdin, 0, SEEK_END);
        printf("Give command: ");
        fgets(command, 10, stdin);
        number_command = atoi(command);

        switch (number_command) {
            case 1:
                printf("Give index: ");
                scanf("%d", &index);

                fseek(stdin, 0, SEEK_END);
                printf("Give type (seaside, mountain or city break): ");
                fgets(type, 50, stdin);
                type[strlen(type)-1] = '\0';
                printf("Give price (double): ");
                scanf("%lf", &price);
                offer = get_element_by_index_offer_service(ui->offersService, index);
                new_offer = create_offer(type, offer->destination, offer->departure_date, price);

                check_errors(ui, update_element_by_index_offers_service(ui->offersService, new_offer, index));


                destroy_offer(new_offer);

                break;
            case 2:
                read_variables(type, destination_for_search, departure_date_for_search, &price);
                offer = create_offer(type, destination_for_search, departure_date_for_search, price);

                check_errors(ui, update_element_by_destination_and_departure_date_offers_service(ui->offersService, offer, destination_for_search, departure_date_for_search));

                destroy_offer(offer);
                break;
            case 0:
                done = 1;
                return;
                break;
            default:
                printf("Wrong command.\n");
        }

    }
}

void print_offer(UI *ui, Offer *offer) {
    printf("%d  Type: %s  Destination: %s Departure date: %s Price: %lf\n",
           get_index_by_element_offer_service(ui->offersService, offer), offer->type,
           offer->destination, offer->departure_date, offer->price);

}

void show_all_offers_UI(UI *ui) {

    DynamicArray *offers = get_all_elements_offers_service(ui->offersService);

    for (int i = 0; i < offers->length; i++)
        print_offer(ui, offers->elems[i]);

    destroy_dynamic_array(offers);
}

void show_all_offers_with_dest_substring_and_asc_by_price_UI(UI *ui) {
    char substring[256];
    printf("Give substring to search for in destination: ");
    fgets(substring, 256, stdin);
    substring[strlen(substring) - 1] = '\0';

    DynamicArray *offers = get_all_elements_with_dest_substring_and_sorted_by_price_asc_offers_service(
            ui->offersService, substring);

    for (int i = 0; i < offers->length; i++)
        print_offer(ui, offers->elems[i]);

    destroy_dynamic_array(offers);
}

void show_all_offers_same_destination_month_asc_ui(UI *ui) {
    char destination[256];
    printf("Give destination to search for: ");
    fgets(destination, 256, stdin);
    destination[strlen(destination) - 1] = '\0';

    DynamicArray *offers = get_elements_same_destination_month_asc_service(ui->offersService, destination);

    for (int i = 0; i < offers->length; i++)
        print_offer(ui, offers->elems[i]);

    destroy_dynamic_array(offers);
}


void show_all_offers_with_same_type_and_bigger_than_a_date_ui(UI* ui) {
    char type[50], departure_date[100];
    printf("Give type to search for: ");
    fgets(type, 256, stdin);
    type[strlen(type) - 1] = '\0';
    printf("Give departure date to search for (dd/mm/yyyy): ");
    fgets(departure_date, 256, stdin);
    departure_date[strlen(departure_date) - 1] = '\0';

    DynamicArray* offers = get_all_offers_of_same_type_bigger_than_a_date_offer_service(ui->offersService, type, departure_date);

    for (int i = 0; i < offers->length; i++)
        print_offer(ui, offers->elems[i]);

    destroy_dynamic_array(offers);


}

void undo_ui(UI* ui) {
    undo(ui->offersService->ur, &ui->offersService->offersRepo->da);
}
void redo_ui(UI* ui) {
    redo(ui->offersService->ur, &ui->offersService->offersRepo->da);
}

void start_ui(UI *ui) {
    int done = 0;
    char command[10];
    unsigned long size_read_command = 10;
    int number_command;
    while (done == 0) {
        print_menu();
        fseek(stdin, 0, SEEK_END);
        printf("Give command: ");
        fgets(command, 10, stdin);
        if (strlen(command) - 1 > 1)
            command[strlen(command) - 1] = '\0';
        number_command = atoi(command);
        

        switch (number_command) {
            case 1:
                add_offer_ui(ui);
                break;
            case 2:
                delete_offer_ui(ui);
                break;
            case 3:
                update_offer_UI(ui);
                break;
            case 4:
                show_all_offers_UI(ui);
                break;
            case 5:
                show_all_offers_with_dest_substring_and_asc_by_price_UI(ui);
                break;
            case 6:
                show_all_offers_same_destination_month_asc_ui(ui);
                break;
            case 7:
                show_all_offers_with_same_type_and_bigger_than_a_date_ui(ui);
                break;
            case 8:
                undo_ui(ui);
                break;
            case 9:
                redo_ui(ui);
                break;
            case 0:
                done = 1;
                break;
            default:
                printf("Wrong command.\n");

        }


    }

}




