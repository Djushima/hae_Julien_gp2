// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "Lib.hpp"
#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>

using namespace sf;

class Entity {
public:
	sf::Shape *sprite = nullptr;			//Rendu
	sf::FloatRect box;						//Collision
	bool movable = false;

	Entity(sf::Shape *forme, Vector2f Pos, sf::Color FillColor, sf::Color OutColor) {
		this->sprite = forme;
		this->sprite->setPosition(Pos);
		this->sprite->setFillColor(FillColor);
		this->sprite->setOutlineColor(OutColor);
		this->sprite->setOutlineThickness(1);
		this->box = forme->getGlobalBounds();
	}

	~Entity(){
		if (sprite) delete sprite;
		sprite = nullptr;
	}

	void _draw(sf::RenderWindow &win) {
		win.draw(*sprite);
	}

	virtual void Move() {
	}

	virtual void Rebond(Entity* Object2) {
	}
};

class Projectile : public Entity {
private:
	const double PI = 3.141592653589793238463;
	Vector2f dir;
	float x, y;

public:
	bool Bounced;

	Projectile(float angle, sf::Shape *forme, Vector2f Pos, sf::Color FillColor, sf::Color OutColor) : 
	Entity(forme, Pos, FillColor, OutColor) {
		this->dir = Vector2f(cos(angle), sin(angle));
		this->Bounced = false;
		this->sprite->setRotation(angle * (180 / PI));
		this->x = this->sprite->getPosition().x;
		this->y = this->sprite->getPosition().y;
		this->movable = true;
	}

	~Projectile(){
		if (dir != Vector2f(0, 0)) dir = Vector2f(0, 0);
	}

	void Move() {
		x += dir.x * 2;
		y += dir.y * 2;
		this->sprite->setPosition(x,y);
		this->box = this->sprite->getGlobalBounds();
		Entity::Move();
	}

	void Rebond(Entity* Object2) {
		auto Obj1Pos = this->sprite->getPosition();
		auto Obj2Pos = Object2->sprite->getPosition();
		auto Obj2Ofs = Object2->box;
		if ((Obj1Pos.x > Obj2Pos.x + Obj2Ofs.width) || (Obj1Pos.x < Obj2Pos.x))
			this->dir = Vector2f(-this->dir.x, this->dir.y);
		else if ((Obj1Pos.y > Obj2Pos.y + Obj2Ofs.height) || (Obj1Pos.y < Obj2Pos.y))
			this->dir = Vector2f(this->dir.x, -this->dir.y);
		this->sprite->setRotation(PI - this->sprite->getRotation());
		this->Bounced = true;
	}

};

static std::vector<Entity*> Objects;
static std::vector<Projectile*> ProjectileTab;
static Vector2f SquarePos;

b2Vec2 gravity(0.0f, 0.0f);
b2World world(gravity);


RectangleShape* initSquareRender(int x, int y) {
	auto Square = new RectangleShape(Vector2f(x,y));
	return Square;
}

void initMap() {
	auto Char = new Entity(
		initSquareRender(16, 16),
		Vector2f(SquarePos.x = 640, SquarePos.y = 360),
		sf::Color(0xFF0101ff),
		sf::Color(0x0107FFff));
	Char->sprite->setOrigin(Vector2f(8, 8));
	Char->movable = true;
	Objects.push_back(Char);

	auto NBorder = new Entity(
		initSquareRender(1280, 20),  
		Vector2f(0, 0), 
		sf::Color(0xB226FFff), 
		sf::Color::Transparent);
	Objects.push_back(NBorder);

	auto SBorder = new Entity(
		initSquareRender(1280, 20), 
		Vector2f(0, 700), 
		sf::Color(0xB226FFff), 
		sf::Color::Transparent);
	Objects.push_back(SBorder);

	auto EBorder = new Entity(
		initSquareRender(20, 720), 
		Vector2f(0, 0), 
		sf::Color(0xB226FFff), 
		sf::Color::Transparent);
	Objects.push_back(EBorder);

	auto WBorder = new Entity(
		initSquareRender(20, 720), 
		Vector2f(1260, 0),
		sf::Color(0xB226FFff),
		sf::Color::Transparent);
	Objects.push_back(WBorder);
}

void drawMap(sf::RenderWindow &win) {
	for (int i = 0; i < Objects.size(); i++)
		Objects[i]->_draw(win);
}

void drawCible(sf::RenderWindow &win) {
	sf::Vertex line[] =
	{
		sf::Vertex(Objects[0]->sprite->getPosition()),
		sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(win)))
	};
	sf::CircleShape cible(5);
	line->color = sf::Color(0xFF0101ff);
	cible.setOutlineColor(sf::Color(0xE80C2Eff));
	cible.setFillColor(sf::Color::Transparent);
	cible.setOutlineThickness(1);
	cible.setOrigin(5, 5);
	cible.setPosition(sf::Vector2f(sf::Mouse::getPosition(win)));
	win.draw(cible);
	win.draw(line, 2, sf::Lines);
}

void drawProjectile(sf::RenderWindow &win) {
	auto angle = atan2(sf::Mouse::getPosition(win).y - Objects[0]->sprite->getPosition().y, sf::Mouse::getPosition(win).x - Objects[0]->sprite->getPosition().x);
	auto Proj = new Projectile(
		angle,
		initSquareRender(7, 2),
		Vector2f(Objects[0]->sprite->getPosition().x + cos(angle) * 15, Objects[0]->sprite->getPosition().y + sin(angle) * 15),
		sf::Color(0x6EF3FFff),
		sf::Color::Transparent);

	Proj->sprite->setOrigin(Vector2f(0, 1));
	Objects.push_back(Proj);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280,720), "SFML works!", sf::Style::Default, settings);	//Creer une fenetre appelé "SFML Works" de taille 200x200)
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

	sf::Text fpsText;
	sf::Text MousePos;
	MousePos.setPosition(975, 0);
	MousePos.setFont(font);
	fpsText.setFont(font);
	MousePos.setFillColor(sf::Color::Blue);
	fpsText.setFillColor(sf::Color::Red);

	initMap();
	float squareSpeed = 1;


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

				if (event.key.code == sf::Keyboard::Space)
					drawProjectile(window);
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (squareSpeed < 3)
				squareSpeed += 0.05f;
			SquarePos.x -= squareSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (squareSpeed < 3)
				squareSpeed += 0.05f;
			SquarePos.x += squareSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (squareSpeed < 3)
				squareSpeed += 0.05f;
			SquarePos.y -= squareSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (squareSpeed < 3)
				squareSpeed += 0.05f;
			SquarePos.y += squareSpeed;
		}
		else
			if (squareSpeed > 0)
				squareSpeed -= 0.3f;


		window.clear();																				//Nettoie la frame

		drawMap(window);
		window.draw(fpsText);
		window.draw(MousePos);
		drawCible(window);
		Vector2f LastPos = Objects[0]->sprite->getPosition();
		Objects[0]->sprite->setPosition(SquarePos.x, SquarePos.y);
		Objects[0]->box = Objects[0]->sprite->getGlobalBounds();

		for (int i = 0; i < Objects.size(); i++) {
			Objects[i]->Move();
		}

		for (int i = 1; i < Objects.size(); i++)
		{
			auto mb = Objects[0]->sprite->getGlobalBounds();
			auto extbounds = Objects[i]->sprite->getGlobalBounds();
			if (Objects[0]->box.intersects(Objects[i]->box))
			{
				if (!Objects[i]->movable)	//Cas: Tank1 vs Wall
				{
					SquarePos = LastPos;
					Objects[0]->sprite->setPosition(LastPos);
				}
				else						//Cas: Tank vs Proj
				{
					Objects.erase(Objects.begin()+i);
					Objects.erase(Objects.begin());
					break;
				}
			}

			
			for (int j = 1; j < Objects.size(); j++)
			{
				if (i != j && Objects[i]->box.intersects(Objects[j]->box))
					if (Objects[i]->movable && !Objects[j]->movable) //Cas: Proj vs Wall = Rebond || Destroy
					{
						Projectile * proj = dynamic_cast<Projectile*>(Objects[i]);
						if (proj->Bounced)
							Objects.erase(Objects.begin() + i);
						else
							proj->Rebond(Objects[j]);
						break;
					}
					else if (Objects[i]->movable && Objects[j]->movable) //Cas: Proj vs Proj = Destroy
					{
						Objects.erase(Objects.begin() + i);
						Objects.erase(Objects.begin() + j-1);
						break;
					}
			}
			
		}

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
