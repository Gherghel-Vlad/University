#pragma once

#include "../Matrix.h"

class MatrixIterator {

	friend class Matrix;
private:
	const Matrix& matrix;

	DLLNode* currentNode;
	int currentLine;
	int currentColumn;
public:
	MatrixIterator(const Matrix& matrix);

	TElem getCurrent();
	bool valid();
	void next();
};
