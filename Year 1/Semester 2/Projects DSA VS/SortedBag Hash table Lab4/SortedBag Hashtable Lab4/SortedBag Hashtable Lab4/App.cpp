#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>

using namespace std;
bool relation21(TComp r1, TComp r2) {
	return r1 <= r2;
}

int main() {
	testAll();
	testAllExtended();
	
	cout << "Start extra operation testing" << endl;


	SortedBag bag{ relation21 };

	for (int i = 0; i < 10; i++)
		bag.add(i);


	// print the list
	SortedBagIterator it = bag.iterator();

	while (it.valid()) {
		cout << it.getCurrent() << " ";
		it.next();
	}
	cout << endl;
	// delete the fifth element using the iterator

	SortedBagIterator it1 = bag.iterator();
	for (int i = 0; i < 5; i++)
		it1.next();

	it1.remove();
	it1.remove();
	it1.remove();
	it1.remove();
	it1.remove(); // all elements
	//it1.remove(); // with this one it throw exception

	if (it1.valid() == true)
		throw exception();

	// print the list again
	SortedBagIterator it2 = bag.iterator();

	while (it2.valid()) {
		cout << it2.getCurrent() << " ";
		it2.next();
	}
	cout << endl;

	cout << "Test over" << endl;
	system("pause");
}
