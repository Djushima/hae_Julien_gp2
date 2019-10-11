
#include "pch.h"
#include "intArray.hpp"

int intArray::TEST = 66;

bool intArray::ensure(int size)
{
	if (maxSize > size) return true;

	int * dataTemp = new int[size];
	for (int i = 0; i < curSize; i++)
	{
		dataTemp[i] = data[i];
	}
	delete(data);
	data = dataTemp;

	maxSize = size;
	printf("IN\n");
	return true;
}

void intArray::push_back(int elem) {
	ensure(curSize + 1);
	data[curSize] = elem;
	curSize++;
}

void intArray::push_first(int elem) {
	ensure(curSize + 1);
	for (int i = curSize; i > 0; i--) {
		data[i] = data[i - 1];
	}
	data[0] = elem;
	curSize++;
}

void intArray::insert(int pos, int elem) {
	ensure( (pos >= curSize) ? (pos + 1) : (curSize + 1) );
	for (int i = curSize; i > pos; i--) {
		data[i] = data[i - 1];
	}
	data[pos] = elem;
	if (pos >= curSize)
		curSize = pos + 1;
	else
		curSize++;
}
