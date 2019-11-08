// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "Lib.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>

using namespace sf;

float rd() {
	return 1.0 * rand() / RAND_MAX;
}

sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

void drawCurve(sf::RenderWindow &win, sf::Clock clock) {
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Blue;
	int nb = 100;
	float stride = 1280.0 / nb;
	int ofsX = -200;
	float now = clock.getElapsedTime().asSeconds();

	if (fmodf(now, 3.0) <= 1) {
		red.a = 0;
	}

	for (int i = now; i < 1000+now; i++)
	{
		double ratio = 1.0 * i / nb;
		double x = ofsX + stride * i - (now*100);
		double y = 400;

		//y += sin(now) * 200;  //Illustration du sinus.
		y += sin(i *2 + ratio * 2 + now * 5) * (cos(now * 128) * 256);

		//sf::Color c = i % 2 == 0? blue : red;
		sf::Color c = hsv(ratio * 360, 0.8, 0.8);

		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);
	}
	win.draw(va);
}

Vector2i P1, P2, P3, P4;

void drawCatmull(sf::RenderWindow &win, Clock clock) {
	auto now = clock.getElapsedTime().asSeconds();
	sf::VertexArray va(sf::LineStrip);
	sf::CircleShape circle(5);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Blue;
	int nb = 320;
	float stride = 1280.0 / nb;

	std::vector<Vector2f> points;

	/*for (int j = 0; j < 8; ++j) {
		points.push_back(Vector2f(j * 50 + rd() * 20, j * 50 + rd() * 20));		//Tremble
	}*/  

	/*for (int j = 0; j < 8; ++j) {
		Vector2f v(j * 100, j * 100);
		if (j == 0)v.x += 100;
		if (j == 3)v.x += 200;
		points.push_back(v);
	}*/

	points.push_back(sf::Vector2f(P1));
	points.push_back(sf::Vector2f(P2));
	points.push_back(sf::Vector2f(P3));
	points.push_back(sf::Vector2f(P4));


	for (int i = 0; i < nb + 1; ++i) {
		double ratio = 1.0 * i / nb;
		double x = 0.0;
		double y = 0.0;
		sf::Color c = hsv(ratio * 360, 0.8, 0.8);

		Vector2f pos = Lib::plot2(ratio, points);
		x = pos.x;
		y = pos.y;

		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);
	}
	circle.setOrigin(5, 5);

	static float cRatio = 0.0;
	static bool autoreverse = false;
	circle.setPosition(Lib::plot2(autoreverse ? cRatio : (1 - cRatio), points));

	cRatio += 0.01;
	if (cRatio > 1.0) {
		cRatio = 0.0;
		autoreverse = !autoreverse;
	}

	win.draw(va);
	win.draw(circle);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Default, settings);	//Creer une fenetre appelé "SFML Works" de taille 200x200)
	sf::CircleShape shape(100.f, 2 * 3.141569 * 100);												//Creer en mémoire un rond de taille 100f
	shape.setFillColor(sf::Color::Green);															//Set la couleur du rond a Vert
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(0x4887E8));
	window.setVerticalSyncEnabled(true);

	sf::Clock Clock;

	sf::Time appStart = Clock.getElapsedTime();
	sf::Time frameStart = Clock.getElapsedTime();
	sf::Time prevFrameStart = Clock.getElapsedTime();

	float fps[4] = { 0.f, 0.f, 0.f, 0.f };
	int step = 0;

	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text fpsText;
	sf::Text MousePos;
	MousePos.setPosition(975, 0);
	MousePos.setFont(font);
	fpsText.setFont(font);
	MousePos.setFillColor(sf::Color::Blue);
	fpsText.setFillColor(sf::Color::Red);
	int every = 10;

	while (window.isOpen())																			//tout le temps.
	{
		MousePos.setString("MousePos: " + (std::to_string(sf::Mouse::getPosition(window).x) + " / " + (std::to_string(sf::Mouse::getPosition(window).y))));
		if (every == 0)
		{
			fpsText.setString("FPS: " + std::to_string(fps[(step - 1) % 4]));
			every = 100;
		}
		every--;

		frameStart = Clock.getElapsedTime();
		sf::Event event;																			//recup les event clavier/pad	
		while (window.pollEvent(event))									
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::I)
					printf("Instant fps %f\n", fps[(step-1)%4]);

				if (event.key.code == sf::Keyboard::F)
					printf("fps %f\n", 0.25*(fps[0] + fps[1] + fps[2] + fps[3]));
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)
					P1 = sf::Mouse::getPosition(window);
				if (event.key.code == sf::Keyboard::F2)
					P2 = sf::Mouse::getPosition(window);
				if (event.key.code == sf::Keyboard::F3)
					P3 = sf::Mouse::getPosition(window);
				if (event.key.code == sf::Keyboard::F4)
					P4 = sf::Mouse::getPosition(window);
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();																				//Nettoie la frame
		//window.draw(shape);																			//On dessine la forme.
		window.draw(fpsText);
		window.draw(MousePos);
		//drawCurve(window, Clock);
		drawCatmull(window, Clock);
		window.display();																			//Ca dessine et attends la vsync.

		fps[step % 4] = 1.0 / (frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;

		step++;
	}

	return 0;
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
