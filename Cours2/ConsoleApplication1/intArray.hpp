#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

class intArray {

public:

	std::string name;
	int * data; //Tableau dynamique qui contient les données
	int maxSize = 0;
	int curSize = 0;
	//membre TEST statique (qui n'existe qu'à un seul endroit)
	static int TEST;

	intArray(int size, const char * name = nullptr) {
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

	}

	~intArray() {

		printf("Detruite! %s\n", name.c_str());
	}
};