#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


int main() {
//	testAll();
//	testAllExtended();
	FixedCapBiMap f = FixedCapBiMap(5);
    f.add(2, 2);
    f.add(2, 3);
    f.add(4, 2);
    f.add(5, 2);

    printf("%d\n", f.size());

    f.removeKey(4);

    printf("%d\n", f.size());

    f.removeKey(2);

    printf("%d\n", f.size());

    f.removeKey(5);

    printf("%d\n", f.size());

    cout << "That's all!" << endl;
	system("pause");
	return 0;
}


