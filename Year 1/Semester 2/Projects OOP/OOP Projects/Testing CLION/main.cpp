//
// Created by Admin on 3/21/2021.
//

#include "main.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    int a=6, b=7;
    int *p = new int;
    *p = 6;

    cout << a + b << " " << (*p) << endl;
    assert(a+1==b);
    _CrtDumpMemoryLeaks();
    return 0;
}