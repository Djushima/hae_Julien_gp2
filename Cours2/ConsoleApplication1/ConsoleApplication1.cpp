// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "intArray.hpp"
#include <iostream>

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

		tab0.ensure(17);

	}
	//ici tableau détruit.
	{
		//Variable dynamique
		intArray * tab1 = new intArray(16, nameTab1);
		tab1->ensure(20);
		delete(tab1);
		tab1 = nullptr;
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
