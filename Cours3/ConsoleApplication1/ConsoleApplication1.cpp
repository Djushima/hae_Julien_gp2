// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "intArray.hpp"
#include "utile.hpp"
#include "List.hpp"
#include "Tree.hpp"

void assert(bool condition) { if (!condition) throw std::exception("non"); }

void testInlist() {
	IntList l(8);

	IntList * MaList = new IntList(8);

	MaList->Append(65);
	assert(MaList->Length() == 2);
	MaList = MaList->AddFirst(20);
	assert(MaList->Length() == 3);
	MaList = MaList->Remove(65);
	assert(MaList->Length() == 2);
	assert(MaList->Contains(20) == true);
	assert(MaList->Contains(65) == false);
}

void testFloatTree() {
	FloatTree * tree = new FloatTree();
	Node<float> * leaf = new FloatNode(8);

	
	//leaf->insertLeft(4);
	//assert(leaf->left->elem == 4);

	//leaf->insertRight(9);
	//assert(leaf->right->elem == 9);

	//assert(leaf->getLength() == 3);

	leaf->insert(4);
	leaf->insert(9);
	leaf->insert(16);
	leaf->insert(3);
	leaf->insert(5);

	tree->root = leaf;

	assert(leaf->Contains(16) == true);
	leaf->remove(16);
	assert(leaf->Contains(16) == false);
	
	
	tree->dfsPrint();

	int k = 0;
}


int main()
{
	//testInlist();

	testFloatTree();

	/*double temps1, temps2;
	{
		double t0 = TimeUtil::getTimestamp();
		intArray t;
		t.fillWithRandom(256);
		t.insertSort();
		for (int i = 0; i < t.getLength() - 1; i++)
			assert(t.get(i) <= t.get(i + 1));

		double t1 = TimeUtil::getTimestamp();
		temps1 = t1 - t0;
		printf("Temps de calcul: %f s for %d\n", temps1, t.getLength());
		int j = 0;
	}*/

	/*{
		double t0 = TimeUtil::getTimestamp();
		intArray t;
		t.fillWithRandom(1024);
		t.insertSort();
		for (int i = 0; i < t.getLength() - 1; i++)
			assert(t.get(i) <= t.get(i + 1));

		double t1 = TimeUtil::getTimestamp();
		temps2 = t1 - t0;
		printf("Temps de calcul: %f s for %d\n", (temps2), t.getLength());
		int j = 0;
	}*/

	/*{
		double t0 = TimeUtil::getTimestamp();
		intArray t;
		t.set(0, 1);
		t.set(1, 3);
		t.set(2, 8);
		t.set(3, 10);
		t.set(4, 15);
		t.set(5, 17);
		t.set(6, 20);
		int pos = t.SearchPosition(12);
		printf("Pos Search: %i\n", pos);
		double t1 = TimeUtil::getTimestamp();
		temps1 = t1 - t0;
	}

	{
		double t0 = TimeUtil::getTimestamp();
		intArray t;
		t.set(0, 1);
		t.set(1, 3);
		t.set(2, 8);
		t.set(3, 10);
		t.set(4, 15);
		t.set(5, 17);
		t.set(6, 20);
		int pos = t.binarySearch(12);
		printf("Pos BinarySearch: %i\n", pos);
		double t1 = TimeUtil::getTimestamp();
		temps2 = t1 - t0;
	}

	float rapport = temps1 / temps2;
	printf("Temps Search: %f\n", temps1);
	printf("Temps BinarySearch: %f\n", temps2);
	printf("Temps Binaire %f fois plus rapide que Temps Search", rapport);*/

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
