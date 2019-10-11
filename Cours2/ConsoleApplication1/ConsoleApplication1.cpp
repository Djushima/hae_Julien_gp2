// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "intArray.hpp"
#include <iostream>

void assert(bool condition) { if (!condition) throw std::exception("non"); }

int main()
{
    std::cout << "Hello World!\n";
	printf("TEST value: %i\n", intArray::TEST);

	auto nameTab0 = "Tab0";
	auto nameTab1 = "Tab1";

	{
		//Variable dynamique
		//auto montableau = new intArray(16);
		//intArray * montableau = new intArray(16);

		//variable locale
		intArray tab0 = intArray(16, nameTab0);
	}
	//ici tableau tab0 détruit.

	{
		//Variable dynamique
		intArray * tab1 = new intArray(16, nameTab1);
		tab1->ensure(17);
		delete(tab1);
		tab1 = nullptr;
	}

	{
		intArray t(16);
		t.set(0, 8);
		t.set(3, 66);
		for (int i = 0; i < t.getLength(); i++) {
			printf("t[%d]: %d\n", i, t.get(i));
		}
	}

	{
		intArray t(10);
		for (int i = 0; i < 6; i++) {
			t.set(i, i*i);
		}
		t.push_back(5);
		t.push_first(2);
		t.insert(3, 88);
	}

	{
		intArray t(1);
		t.set(0, 5);
		t.set(1, 6);
		t.set(2, 10);

		t.insert(t.SearchPosition(1), 1);
		t.insert(t.SearchPosition(6), 6);
		t.insert(t.SearchPosition(8), 8);

		t.Remove(6);
	}

	{
		intArray t;
		t.fillWithRandom(16);
		t.Sort();

		int i = 0;
	}

}



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
