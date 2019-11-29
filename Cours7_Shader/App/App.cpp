// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "Lib.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>
#include "App.h"
#include <sys/stat.h>

using namespace sf;

class Turtle : public sf::ConvexShape {
public:
	sf::Transform m_Trs;

	Turtle() : sf::ConvexShape(3){
		setFillColor(sf::Color(0x75FF30ff));
		setOutlineThickness(2);
		setOutlineColor(sf::Color(0xcd, 0xcd, 0xcd));

		setPoint(0, Vector2f(0, -24));
		setPoint(1, Vector2f(-16, 16));
		setPoint(2, Vector2f(16, 16));
	}

	void setTransform(sf::Transform trs) {
		m_Trs = trs;
	}
};

static sf::Shader * simpleShader = nullptr;
static sf::Shader * redShader = nullptr;
static sf::Shader * bloomShader = nullptr;
static sf::Shader * blurShader = nullptr;
sf::Texture * whiteTex;

static Transform s_Init;
static std::vector<Transform> s_Trs;
static std::vector<Turtle*> s_Turtles;
struct stat Info;
struct stat newInfo;


static void startTransform() {
	s_Init = Transform::Identity;
	s_Init.translate(500, 500);
	s_Init.rotate(90);
}

static void TranslateY(float dy) {
	sf::Transform res;
	res.translate(0, dy);
	s_Trs.push_back(res);
}

static void scaleXY(float dxy) {
	sf::Transform res;
	res.scale(dxy, dxy);
	s_Trs.push_back(res);
}

static void rotate(float degree) {
	sf::Transform res;
	res.rotate(degree);
	s_Trs.push_back(res);
}

static void computeTransform(sf::Transform & result, int step = -1) {
	sf::Transform inter;

	inter.combine(s_Init);

	if (step <= -1) {
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
		}
	}
	else {
		step--;
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
			if (step <= 0)break;
		}
	}
	result = inter;
}

static void plotTurtle() {
	sf::Transform cur;
	computeTransform(cur, s_Trs.size() - 1);
	Turtle *t = new Turtle();
	t->setTransform(cur);
	s_Turtles.push_back(t);
}

enum TurtleCommand {
	AV,
	REC,
	GROSSI,
	L45,
	R45
};

bool startsWith(const char * s0, const char * s1) {
	if (*s0 == 0 && *s1 != 0)
		return false;
	if (*s1 == 0)
		return true;
	if (*s0 != *s1)
		return false;
	else
		return startsWith(s0 + 1, s1 + 1);
}

static std::vector<TurtleCommand> cmd;
static char data[1024];
static void readScript() {
	cmd.clear();
	FILE * f = nullptr;
	auto err = fopen_s(&f, "res/ScriptTortue.txt", "r");
	if (f != nullptr) {
		memset(data, 0, 1024);
		fread(data, 1024, 1, f);
		printf("Read file %s\n", data);
		fclose(f);
		if (stat("res/ScriptTortue.txt", &Info) != 0)
			printf("Stat Error\n");

		char * cur = data;

		bool doContinue = true;
		while (doContinue)
		{
			if (*cur == 0){
				doContinue = false;
				break;
			}
			else {
				if (startsWith(cur, "AV"))
				{
					cmd.push_back(AV);
				}
				else if (startsWith(cur, "REC"))
				{
					cmd.push_back(REC);
				}
				else if (startsWith(cur, "GROSSI"))
				{
					cmd.push_back(GROSSI);
				}
				else if (startsWith(cur, "L45"))
				{
					cmd.push_back(L45);
				}
				else if (startsWith(cur, "R45"))
				{
					cmd.push_back(R45);
				}
				cur = strstr(cur, " ");
				if (!cur)
					break;
				else
					cur++;
			}
		}
	}
	else {
		printf("Cannot Read file %s\n", "res/ScriptTortue.txt");
	}
}

static void PlayTurtle(std::vector<TurtleCommand> cmd, int delta) {
	for (int i = 0; i < cmd.size(); i++)
	{
		switch (cmd[i])
		{
		case AV:
			TranslateY(delta);
			plotTurtle();
			break;

		case REC:
			TranslateY(-delta);
			plotTurtle();
			break;

		case GROSSI:
			scaleXY(2.0);
			plotTurtle();
			break;

		case L45:
			rotate(-45);
			plotTurtle();
			break;

		case R45:
			rotate(45);
			plotTurtle();
			break;
		}
	}
}

static void ResetTurtle() {
	startTransform();

	sf::Transform trs;
	computeTransform(trs);

	for (Turtle * t : s_Turtles) delete t;
	s_Turtles.clear();

	Turtle *t = new Turtle();
	t->setTransform(trs);
	s_Turtles.push_back(t);

	readScript();
};



float rd() {
	return 1.0 * rand() / RAND_MAX;
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
	int every = 10;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	if (!sf::Shader::isAvailable())
		printf("no shader available\n");

	simpleShader = new Shader();
	if (!simpleShader->loadFromFile("res/simple.vert", "res/simple.frag"))
		printf("unable to load shader\n");

	whiteTex = new Texture();
	if (!whiteTex->create(1, 1)) printf("tex crea failed\n");
	whiteTex->setSmooth(true);
	unsigned int col = 0xffffffff;
	whiteTex->update((const sf::Uint8*)&col, 1, 1, 0, 0);

	readScript();
	

	sf::Text fpsText;
	sf::Text MousePos;
	MousePos.setPosition(975, 0);
	MousePos.setFont(font);
	fpsText.setFont(font);
	MousePos.setFillColor(sf::Color::Blue);
	fpsText.setFillColor(sf::Color::Red);

	startTransform();
	plotTurtle();
	int frame = 0;

	while (window.isOpen())																			//tout le temps.
	{
		frame++;
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

				if (event.key.code == sf::Keyboard::Space)
				{
					startTransform();

					sf::Transform trs;
					computeTransform(trs);

					for (Turtle * t : s_Turtles) delete t;
					s_Turtles.clear();

					Turtle *t = new Turtle();
					t->setTransform(trs);
					s_Turtles.push_back(t);
				}

				auto delta = 32;
				if (event.key.code == sf::Keyboard::Up) { TranslateY(-delta); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Down) { TranslateY(delta); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Left) { rotate(-45); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Right) { rotate(45); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Add) {  scaleXY(2.0); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Subtract) { scaleXY(0.5); plotTurtle(); }
				if (event.key.code == sf::Keyboard::Enter) { PlayTurtle(cmd, delta); }
				if (event.key.code == sf::Keyboard::R) { ResetTurtle(); }

			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();																				//Nettoie la frame																			//On dessine la forme.
		window.draw(fpsText);

		for (Turtle * t: s_Turtles)
		{
			RenderStates rs;
			rs.transform = t->m_Trs;
			window.draw(*t, rs);
		}

		if (frame % 60 == 0)
		{
			if (stat("res/ScriptTortue.txt", &newInfo) != 0)
				printf("New Stat Error\n");
			if (newInfo.st_mtime != Info.st_mtime)
				ResetTurtle();
		}


		/*sf::RectangleShape sh(Vector2f(64, 64));
		sh.setPosition(50, 50);
		sh.setTexture(whiteTex);
		simpleShader->setUniform("time", Clock.getElapsedTime().asSeconds());
		window.draw(sh, simpleShader);*/

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
