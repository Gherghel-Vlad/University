//
// Created by Admin on 3/9/2021.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <stdio.h>
#include <assert.h>
#include "./Tests/tests.h"
#include "./UI/ui.h"
#include <crtdbg.h>

int main(){
    test_all(); 
    UI* ui = create_ui();
    initialise_dummy_data_offers_repo(ui->offersService->offersRepo);
    start_ui(ui);
    destroy_ui(ui);


    _CrtDumpMemoryLeaks();
    return 0;
}
