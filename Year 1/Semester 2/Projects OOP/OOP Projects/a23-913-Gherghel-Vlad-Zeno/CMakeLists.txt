cmake_minimum_required(VERSION 3.17)
project(a23_913_Gherghel_Vlad_Zeno C)

set(CMAKE_C_STANDARD 11)

add_executable(a23_913_Gherghel_Vlad_Zeno
        Domain/Offer.h
        Domain/Offer.c
        Domain/DynamicArray.c
        Domain/DynamicArray.h
        Tests/tests.h
        Tests/tests.c
        Repository/OffersRepoDA.c
        Repository/OffersRepoDA.h
        Service/OffersService.c
        Service/OffersService.h
        UI/ui.c
        UI/ui.h
        main.c Validators/OfferValidators.c Validators/OfferValidators.h UndoRedo/UndoRedo.c UndoRedo/UndoRedo.h)
