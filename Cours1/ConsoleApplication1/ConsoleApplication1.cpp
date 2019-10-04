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

int Max(int a, int b)
{
	return (a < b ? b : a);
}

int Min(int a, int b)
{
	return (a < b ? a : b);
}

int StrCmp(char * meule, char * aiguille)
{
	int lenMeule = strlen(meule);
	int lenAiguille = strlen(aiguille);
	int maxLen = Max(lenMeule, lenAiguille);
	int minLen = Min(lenMeule, lenAiguille);

	for (int i = 0; i < minLen; i++)
	{
		if (meule[i] < aiguille[i])
		{
			return -1;
		}
		else if (meule[i] > aiguille[i])
		{
			return 1;
		}
	}
	if (minLen == maxLen) return 0;
	if (minLen == lenMeule) return -1;
	return 1;
}

char * StrStr(char * meuleDeFoin, char * aiguille) 
{
	int lenMeule = strlen(meuleDeFoin);
	for (int i = 0; i < lenMeule; i++)
	{
		if (strncmp(meuleDeFoin, aiguille, strlen(aiguille)) == 0)
			return meuleDeFoin;
		else
			meuleDeFoin++;
	}
	return nullptr;
}

char * StrStr2(char * meuleDeFoin, char * aiguille)
{
	int lenMeule = strlen(meuleDeFoin);
	int lenAiguille = strlen(aiguille);

	for (int i = 0; i < lenMeule; ++i)
	{
		bool found = true;
		for (int j = 0; j < lenAiguille; ++j)
		{
			if (meuleDeFoin[j] != aiguille[j])
			{
				found = false;
				break;
			}
		}
		if (found)
			return meuleDeFoin;
		meuleDeFoin++;
	}
	return nullptr;
}

int main()
{
    std::cout << "Hello World!\n"; 

	/*char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	Memcpy(licorne,vomi, strlen(licorne + 1));
	Memcpy2(licorne, vomi, strlen(licorne + 1));*/

	/*int place;
	place = StrChr(licorne, 'c');
	printf("Emplacement du char: %i\n", place);
	printf("licorne %s\n", licorne);*/

	/*int comp;
	char text1[1024] = "Bonjour";
	char text2[1024] = "Bonsoir";
	comp = StrCmp(text1, text2);
	printf("Comparaison: %i\n", comp);
	comp = strcmp(text1, text2);
	printf("Comparaison: %i\n", comp);
	comp = StrCmp(text2, text1);
	printf("Comparaison: %i\n", comp);
	comp = StrCmp(text1, text1);
	printf("Comparaison: %i\n", comp);*/

	char text[1024] = "Lorem ipsum dolor sit amer";
	char token[1024] = "dolor";

	char * TokenInText = StrStr(text, token);
	int pos = (int)(TokenInText - text);
	printf("le token est en position %d\n", pos);
}
