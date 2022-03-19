
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SparseMatrixDllDSAHmk/MatrixIterator.h"
using namespace std;


int main() {
	//testAll();
	//testAllExtended();

	Matrix m(4, 4);
	m.modify(1, 1, 5);
	m.modify(0, 0, 5);
	m.modify(2, 3, 5);
	m.modify(1, 2, 10);
	m.modify(3, 1, 11);

	MatrixIterator iter = m.iterator();
	int count = 0;
	while (iter.valid()) {
		cout << iter.getCurrent() << "  ";
		iter.next();
		count++;
		if (count % 4 == 0)
			cout << "\n";
	}
	cout << count;

	cout << "Test End" << endl;
	system("pause");
}