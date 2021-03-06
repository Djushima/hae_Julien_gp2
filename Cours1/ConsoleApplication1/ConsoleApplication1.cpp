// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

static void TestRec();

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

	/*char text[1024] = "Lorem ipsum dolor sit amer";
	char token[1024] = "dolor";

	char * TokenInText = StrStr(text, token);
	int pos = (int)(TokenInText - text);
	printf("le token est en position %d\n", pos);*/

	TestRec();
}

int add(int a, int b)
{
	int i = 0;
	for (i = 0; i < a + b; ++i);
	return i;
}

int add1(int a, int b)
{
	int val = a;
	for (int i = 0; i < b; ++i)
		val++;
	return val;
}

int addRec(int a, int b)
{
	if (a == 0)
		return b;
	else
		return addRec(a - 1, b + 1);
}

int addRec2(int a, int b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return b;
	else
		return 1+ addRec2(a-1, b);
}

int subRec(int a, int b)
{
	if (b == 0) return a;
	if (a == 0) return -b;
	if (b < 0) return subRec(a + 1, b + 1);
	if (b > 0) return subRec(a-1, b-1);
}

int subRec2(int a, int b)
{
	if (b == 0) return a;
	else if (b > 0)
		return subRec2(a, b - 1) - 1;
	else
		return subRec2(a, b + 1) + 1;
}

int mulRec(int a, int b)
{
	if (b == 0 || a == 0) return 0;
	if (b == 1) return a;
	if (a == 1) return b;
	if (b < 0) return -mulRec(a, -b);
	return a + mulRec(a, b - 1);

}

int divRec(int a, int b)
{
	if (a == 0)				return 0;
	if (b < 0 && a < 0)		return -divRec(a, b);
	if (a < 0)				return -divRec(-a, b);
	if (b < 0)				return -divRec(a, -b);
	if (a < b)				return 0;
	return 1 + divRec(a - b, b);
}

int modRec(int a, int b)
{
	return a - mulRec(b, divRec(a, b));
}

int divModRec1(int a, int b, int *rest)
{
	if (a == 0)				return 0;
	if (b < 0 && a < 0)		return -divRec(a, b);
	if (a < 0)				return -divRec(-a, b);
	if (b < 0)				return -divRec(a, -b);
	if (a < b)
	{
		*rest = a;
		return 0;
	}
	return 1 + divModRec1(a - b, b, rest);
}

int DivModRec2(int a, int b, int *rest)
{
	if (a == 0)
	{
		*rest = 0;
		return 0;
	}
	if (b < 0 && a < 0)
	{
		int subRest = 0;
		int divRem = DivModRec2( a, b, &subRest);
		*rest = -subRest;
		return divRem;
	}
	if (a < 0)
	{
		int subRest = 0;
		int divRem = DivModRec2(-a, b, &subRest);
		*rest = -subRest;
		return divRem;
	}
	if (b < 0)
	{
		int subRest = 0;
		int divRem = DivModRec2(a, -b, &subRest);
		*rest = -subRest;
		return divRem;
	}
	if (a < b)
	{
		*rest = a;
		return 0;
	}
	return 1 + DivModRec2(a - b, b, rest);
}

int StrlenRec(const char * str)
{
	if (*str == 0)
		return 0;
	return 1 + StrlenRec(str+1);
}

void StrCpyRec(char *dest, const char *src)
{
	*dest = *src;
	if (*src == 0) return;
	else
	{
		StrCpyRec(dest + 1, src + 1);
	}
}

void ZeroMemory(char * dst, int size)
{
	if (size == 0) return;
	else
	{
		*dst = 0;
		ZeroMemory(dst + 1, size - 1);
	}
}

void MemCpyRec(char * dst, const char * src, int size)
{
	if (size < 0) return;
	else
	{
		*dst = *src;
		MemCpyRec(dst + 1, src + 1, size - 1);
	}
}

int StrcmpRec(char *str0, char * str1)
{
	if (*str0 == 0 && *str1 == 0) return 0;
	if (*str0 == 0) return 1;
	if (*str1 == 0) return -1;
	if (*str0 < *str1) return 1;
	if (*str0 > *str1) return -1;
	return StrcmpRec(str0 + 1, str1 + 1);
}

void StrcatRec(char * str0, char * str1)
{
	if (*str1 == 0)
	{
		*str0 = '\0';
		return;
	}
	if (*str0 == 0)
	{
		*str0 = *str1;
		return StrcatRec(str0 + 1, str1 + 1);
	}
	return StrcatRec(str0 + 1, str1);
}

int StrchrRec(char* str, char token, char * _start)
{
	if (*str == 0) return -1;
	if (*str == token) return str - _start;

	return StrchrRec(str + 1, token, _start);
}

void assert(bool condition) { if (!condition) throw std::exception("non"); }

char * StrStrRec(char * meuleDeFoin, char * aiguille)
{
	if (strlen(meuleDeFoin) < strlen(aiguille))		return nullptr;
	
	if (strncmp(meuleDeFoin, aiguille, strlen(aiguille)) == 0)
		return meuleDeFoin;
	else
		StrStrRec(meuleDeFoin + 1, aiguille);
}

bool startWith(const char * s0, const char * s1)
{
	if (*s0 == 0 && *s1 != 0) return false;
	if (*s1 == 0) return true;
	if (*s0 != *s1) return false;
	else return startWith(s0 + 1, s1 + 1);
}

const char * StrStrRec2(const char * s0, const char * s1)
{
	if (startWith(s0, s1)) return s0;
	else return StrStrRec2(s0 + 1, s1);
}

void TestRec() 
{
	int reste = 0;
	int foo = add1(2, 2);
	int foo2 = addRec(2, 3);
	int foo3 = addRec2(4, 2);
	int foo4 = subRec(4, 6);
	int foo5 = mulRec(-3, 3);
	int foo6 = divRec(-15, 2);
	int foo7 = modRec(15, 2);
	int foo8 = divModRec1(15, 2, &reste);
	int foo9 = DivModRec2(15, 2, &reste);
	
	int len = StrlenRec("Sapin");

	char dst[150];
	StrCpyRec(dst, "Bonsoir");
	//printf("%s\n", dst);

	int szBuf = 32;
	char * buffer = (char *)malloc(szBuf+1);
	buffer[32] = 'X';
	ZeroMemory(buffer, szBuf);
	printf("%c\n", buffer[32]);

	char Bonjour[32] = "bonjour";
	char Bonsoir[32] = "bonsoir";
	//MemCpyRec(Bonjour, Bonsoir, strlen(Bonjour)+1);
	printf("%s\n", Bonjour);

	//int val = StrcmpRec(Bonjour, Bonsoir);
	//printf("value: %i\n", val);

	StrcatRec(Bonjour, Bonsoir);
	printf("value: %s\n", Bonjour);

	char p1[64] = "Ohayo Oyasumi Konnichiwa Konbanwa";
	char p2[32] = "Oyasumi";

	int place = StrchrRec(p1, 'y', p1);
	printf("Emplacement du char: %i\n", place);

	char * Order = StrStrRec(p1, p2);
	int pos = (int)(Order - p1);
	printf("le token est en position %d\n", pos);

	int i = 0;
}
