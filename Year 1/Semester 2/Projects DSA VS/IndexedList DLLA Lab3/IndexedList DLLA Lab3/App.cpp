#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "IndexedList.h"
#include "ListIterator.h"
using namespace std;

int main(){
    //testAll();
    //testAllExtended();

    IndexedList list{};

    for (int i = 9; i > 0; i--) {
        list.addToEnd(i);
    }

    ListIterator it = list.iterator();

    cout << "The elements before deleting are: ";

    while (it.valid()) {
        cout << it.getCurrent()  << " ";
        it.next();
    }
    cout << "\n";

    ListIterator it1 = list.iterator();

    for (int i = 0; i < 4; i++) {
        it1.next();
    }

    TElem deletedElem = it1.remove();
    deletedElem = it1.remove();

    while (it1.valid()) {
        cout << it1.getCurrent() << " ";
        it1.next();
    }
    cout << "\nThe deleted element is: " << deletedElem << "\n";
    cout << "The elements after deleting are: ";


    ListIterator it2 = list.iterator();

    while (it2.valid()) {
        cout << it2.getCurrent() << " ";
        it2.next();
    }
    cout << "\n";

    cout<<"Finished LI Tests!"<<endl;
}