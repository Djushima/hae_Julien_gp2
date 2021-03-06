#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

class intArray {

public:

	std::string name;
	int * data; //Tableau dynamique qui contient les donn�es
	int maxSize = 0;
	int curSize = 0;
	//membre TEST statique (qui n'existe qu'� un seul endroit)
	static int TEST;

	intArray(int size = 1, const char * name = "") {
		//on passe name en std::string
		//alloue auto un char * et en fait la copie
		this->name = name;
		printf("Construite! %s\n", this->name.c_str());

		//Version C Old school
		//data = (int * )malloc(size * sizeof(int));
		//memset(sata,0, size * sizeof(int));

		//version C new school
		//data = (int *)calloc(size, sizeof(int));
		//calloc met des zero

		//version c++ safe
		data = new int[size];
		for (int i = 0; i < size; ++i) data[i] = 0;

		//curSize = 0;
		maxSize = size;

	}

	~intArray() {

		printf("Detruite! %s\n", name.c_str());
	}

	bool ensure(int size);

	/*int operator() (int pos) {
		ensure(pos+1);
		return data[pos];
	}

	int & operator[] (int pos) {
		ensure(pos+1);
		return data[pos];
	}*/

	int getLength() {
		return curSize;
	}

	int get(int pos) {
		return data[pos];
	}

	void set(int pos, int elem) {
		ensure(pos+1);
		data[pos] = elem;
		if (curSize <= pos)
			curSize = pos + 1;
	}

	void set_unsafe(int pos, int elem) {
		data[pos] = elem;
		curSize = pos + 1;
	}

	void push_back(int elem);

	void push_first(int elem);

	void insert(int pos, int elem);

	int SearchPosition(int elem);

	void Remove(int elem);

	void RemoveAll();

	void fillWithRandom(int nbElem);

	void Sort();

	void swap(int pos0, int pos1);

	void insertSort();

	int binarySearch(int key) {
		//Demander la recherche entre 0 et la taille
		return _binarysearch(key, 0, getLength());
	}

	int _binarysearch(int key, int start, int end) {
		int pivot = (start + end) / 2;

		if (end <= start) return start;
		if (end == start + 1) {
			if (key > data[start]) return end;
			if (key < data[end]) return start;
			return start;
		}
		if (key == data[pivot]) return pivot;

		if (key < data[pivot]) return _binarysearch(key, start, pivot);
		else return _binarysearch(key, pivot, end);
	}
};