#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SMIterator.h"

#include "SortedMap.h"


#include <iostream>
using namespace std;
bool relatie12(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	testAll();
	testAllExtended();

	SortedMap sm(relatie12);
	sm.add(1, 1);
	sm.add(2, 2);
	sm.add(3, 3);
	sm.add(5, 7);
	sm.add(4, 3);
	SMIterator it1 = sm.iterator();

	for (int i = 0; i < 2; i++) {
		it1.next();
	}

	it1.remove();
	//it1.remove();
	//it1.remove();
	//it1.remove();
	/*while (it1.valid()) {
		TElem e = it1.getCurrent();
		printf(" %d ", e.second);
		it1.next();
	}

	printf("\n");*/
	SMIterator it = sm.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		printf(" %d ", e.second);
		it.next();
	}

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


