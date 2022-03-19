//
// Created by Admin on 3/10/2021.
//

#ifndef A23_913_GHERGHEL_VLAD_ZENO_UI_H
#define A23_913_GHERGHEL_VLAD_ZENO_UI_H

#include "../Service/OffersService.h"
#include "../UndoRedo/UndoRedo.h"

typedef struct {
    OffersService* offersService;
    UndoRedo* ur;
} UI;

UI* create_ui();

void destroy_ui(UI* ui);

void start_ui(UI* ui);

#endif //A23_913_GHERGHEL_VLAD_ZENO_UI_H
