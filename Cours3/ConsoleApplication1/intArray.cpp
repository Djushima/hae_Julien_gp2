
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

int intArray::SearchPosition(int elem) { //TabTrié
	for (int i = 0; i < curSize; i++) {
		if (data[i] >= elem) return i;
	}
	return curSize;
}

void intArray::Remove(int elem) {
	for (int i = 0; i < curSize; i++) {
		if (data[i] == elem) {
			for (int j = i; j < curSize; j++)
				data[j] = (j + 1 < curSize ? data[j + 1] : NULL);
			curSize--;
			//break; Si tu veux enlever que la 1ere occurence.
		}
	}
}

void intArray::RemoveAll() {
	for (int i = 0; i < curSize; i++) {
		data[i] = NULL;
	}
	curSize = 0;
}

void intArray::fillWithRandom(int nbElem)
{
	RemoveAll();
	ensure(nbElem);

	for (int i = 0; i < nbElem; i++)
	{
		int val = std::rand() % 100;
		set(i, val);
	}
}

void intArray::Sort() {
	intArray nuData;
	for (int i = 0; i < curSize; i++) {
		int val = get(i);
		nuData.insert(nuData.SearchPosition(val), val);
	}

	for (int j = 0; j < curSize; j++) {
		set(j, nuData.get(j));
	}
}

void intArray::swap(int pos0, int pos1) {
	int temp = data[pos1];
	data[pos1] = data[pos0];
	data[pos0] = temp;
}

void intArray::insertSort() {
	for (int i = 1; i < curSize; i++)
	{
		int j = i;
		while ((j>0) && data[j] < data[j - 1])
		{
			swap(j, j - 1);
			j--;
		}
	}
}
