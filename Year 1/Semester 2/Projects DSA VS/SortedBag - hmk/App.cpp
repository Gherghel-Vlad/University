#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>
using namespace std;

bool relation12(TComp e1, TComp e2) {
	return e1 <= e2;
}
int main() {
	testAll();
	testAllExtended();
	

	SortedBag sb(relation12);
	sb.add(3);
	sb.add(2);
	sb.add(1);
	sb.add(4);
	sb.add(5);
	sb.add(8);
	sb.add(6);
	sb.add(9);
	sb.add(10);
	sb.add(11);
	sb.addOccurrences(3, 8);
	sb.addOccurrences(8, 7);


	cout << "Test over" << endl;
	system("pause");
}
