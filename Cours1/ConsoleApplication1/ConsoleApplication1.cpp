// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

void Memcpy(char * dest, char * src, int size)
{
	while (size--)
	{
		dest[size] = src[size];
	}
}

void Memcpy2(char * dest, char * src, int size)
{
	for (size; size >= 0; size--)
	{
		dest[size] = src[size];
	}
}

int StrChr(char * grange, char chat) //et StrChr3
{
	//int index = 0;
	char * oldGrange = grange;
	while (*grange) 
	{
		if (*grange == chat)
		{
			//return index;
			return(int) (grange - oldGrange);
		}
		/*else
			index++;*/
		grange++;
	}
	return -1;
}

int StrChr2(char * grange, char chat)
{
	int length = strlen(grange);
	for (int index = 0; index < length; index++)
	{
		if (grange[index] == chat)
			return index;
	}
	return -1;
}

int main()
{
    std::cout << "Hello World!\n"; 

	char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	int place;
	//Memcpy(licorne,vomi, strlen(licorne + 1));
	//Memcpy2(licorne, vomi, strlen(licorne + 1));
	place = StrChr(licorne, 'c');

	printf("Emplacement du char: %i\n", place);
	printf("licorne %s\n", licorne);
}
