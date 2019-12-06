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
	bool movable = false, playable = false, destroyed = false;

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
		if (sprite != nullptr)
			win.draw(*sprite);
	}

	virtual void Move() {
	}

	virtual void Rebond(Entity* Object2) {
	}

	void Destroyed(std::vector<Entity*> Objects, int player) {
		delete Objects[player]->sprite;
		Objects[player]->box = FloatRect(-10, -10, 0, 0);
		Objects[player]->sprite = nullptr;
		destroyed = true;
	}
};

class Projectile : public Entity {
private:
	const double PI = 3.141592653589793238463;
	const int speed = 4;
	Vector2f dir;
	float x, y;

public:
	bool Bounced;

	Projectile(float angle, sf::Shape *forme, Vector2f Pos, sf::Color FillColor, sf::Color OutColor) : 
	Entity(forme, Pos, FillColor, OutColor) {
		this->dir = Vector2f(cos(angle), sin(angle));
		this->Bounced = false;
		this->sprite->setRotation(angle * (180 / PI) -90);
		this->x = this->sprite->getPosition().x;
		this->y = this->sprite->getPosition().y;
		this->movable = true;
	}

	~Projectile(){
		if (dir != Vector2f(0, 0)) dir = Vector2f(0, 0);
	}

	void Move() {
		x += dir.x * speed;
		y += dir.y * speed;
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
static std::vector<float> LastCible{ 45, 45 };
static std::vector<Vector2f> LastPos{Vector2f(640,360) , Vector2f(0,0)};
static Vector2f SquarePos1, SquarePos2;
const double PI = 3.141592653589793238463;

RectangleShape PlayButton, QuitButton;
CircleShape a_Button, b_Button;
Text Title, PlayText, QuitText;
Texture * A_ButtonTex = new Texture(), *B_ButtonTex = new Texture(), *BG = new Texture(), * Wall = new Texture(), * Bullet1 = new Texture(), * Bullet2 = new Texture();
Font font;


RectangleShape* initSquareRender(int x, int y) {
	auto Square = new RectangleShape(Vector2f(x,y));
	return Square;
}

void initMap() {
	if (!Wall->loadFromFile("Textures/Wall.png"))
		printf("Wall Texture Error Load");
	Wall->setSmooth(true);
	Wall->setRepeated(true);
	if (!BG->loadFromFile("Textures/Background.png"))
		printf("Wall Texture Error Load");
	BG->setSmooth(true);
	BG->setRepeated(true);
	if (!Bullet1->loadFromFile("Textures/bullet1.png"))
		printf("Wall Texture Error Load");
	Bullet1->setSmooth(true);
	if (!Bullet2->loadFromFile("Textures/bullet2.png"))
		printf("Wall Texture Error Load");
	Bullet2->setSmooth(true);

	auto Char1 = new Entity(
		initSquareRender(15, 15),
		Vector2f(SquarePos1.x = 425, SquarePos1.y = 360),
		sf::Color(0xFF0101ff),
		sf::Color(0x0107FFff));
	Char1->sprite->setOrigin(Vector2f(8, 8));
	Char1->movable = true;
	Char1->playable = true;
	Objects.push_back(Char1);

	auto Char2 = new Entity(
		initSquareRender(15, 15),
		Vector2f(SquarePos2.x = 850, SquarePos2.y = 360),
		sf::Color(0x3550FFff),
		sf::Color(0x0107FFff));
	Char2->sprite->setOrigin(Vector2f(8, 8));
	Char2->movable = true;
	Char2->playable = true;
	Objects.push_back(Char2);

	auto NBorder = new Entity(
		initSquareRender(1280, 50),  
		Vector2f(0, 0), 
		sf::Color(0xFFFFFFff), 
		sf::Color::Black);
	NBorder->sprite->setTexture(Wall);
	NBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	NBorder->box = NBorder->sprite->getGlobalBounds();
	Objects.push_back(NBorder);

	auto SBorder = new Entity(
		initSquareRender(1280, 50), 
		Vector2f(0, 670), 
		sf::Color(0xFFFFFFff), 
		sf::Color::Black);
	SBorder->sprite->setTexture(Wall);
	SBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	SBorder->box = SBorder->sprite->getGlobalBounds();
	Objects.push_back(SBorder);

	auto EBorder = new Entity(
		initSquareRender(620, 50), 
		Vector2f(1280, 50), 
		sf::Color(0xFFFFFFff), 
		sf::Color::Black);
	EBorder->sprite->setTexture(Wall);
	EBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	EBorder->sprite->setRotation(90);
	EBorder->box = EBorder->sprite->getGlobalBounds();
	Objects.push_back(EBorder);

	auto WBorder = new Entity(
		initSquareRender(620, 50), 
		Vector2f(50, 50),
		sf::Color(0xFFFFFFff),
		sf::Color::Black);
	WBorder->sprite->setTexture(Wall);
	WBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	WBorder->sprite->setRotation(90);
	WBorder->box = WBorder->sprite->getGlobalBounds();
	Objects.push_back(WBorder);
}

void drawMap(sf::RenderWindow &win) {
	RectangleShape Background;
	Background.setSize(Vector2f(1280, 720));
	Background.setTexture(BG);

	auto k = 256 * 8;
	Background.setTextureRect(IntRect(0, 0, k, k));
	
	win.draw(Background);
	for (int i = 0; i < Objects.size(); i++)
		Objects[i]->_draw(win);
}

/*void drawCibleSouris(sf::RenderWindow &win) {
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
}*/

void drawCible(sf::RenderWindow &win, float X, float Y, int player)
{
	sf::Shape *Canon = initSquareRender(10, 5);
	Canon->setOrigin(0, 2.5);
	Canon->setPosition(Objects[player]->sprite->getPosition());
	if (X > 20 || X < -20 || Y < -20 || Y>20)
	{
		Canon->setRotation(atan2(Y, X) * (180 / PI));
		LastCible[player] = atan2(Y, X);
	}
	else if ((X > -20 && X < 20) && (Y > -20 && Y < 20))
		Canon->setRotation(LastCible[player] * (180 / PI));
	win.draw(*Canon);
}

void drawProjectile(sf::RenderWindow &win, int player) {
	auto angle = LastCible[player];
	auto Proj = new Projectile(
		angle,
		initSquareRender(10, 16),
		Vector2f(Objects[player]->sprite->getPosition().x + cos(angle) *15, Objects[player]->sprite->getPosition().y + sin(angle) *15),
		sf::Color(0xFFFFFFff),
		sf::Color::Transparent);
	player == 0 ? Proj->sprite->setTexture(Bullet1) : Proj->sprite->setTexture(Bullet2);
	Proj->sprite->setOrigin(Vector2f(5, 0));
	Objects.push_back(Proj);
}

void initMenu() {
	font.loadFromFile("arial.ttf");
	Title.setString("Un jeu de Tank");
	Title.setStyle(sf::Text::Underlined + sf::Text::Italic);
	Title.setFont(font);
	Title.setFillColor(sf::Color::Red);
	Title.setPosition(1280 / 2.8, 720 / 7);

	PlayButton.setSize(Vector2f(1280 / 3, 720 / 6));
	PlayButton.setPosition(Vector2f(1280 / 3, 720 / 4));
	PlayText.setString("Jouer!");
	PlayText.setFont(font);
	PlayText.setFillColor(sf::Color::Black);
	PlayText.setPosition(Vector2f(PlayButton.getGlobalBounds().left + PlayButton.getGlobalBounds().width / 2.2, PlayButton.getGlobalBounds().top + PlayButton.getGlobalBounds().height / 3));

	QuitButton.setSize(Vector2f(1280 / 3, 720 / 6));
	QuitButton.setPosition(Vector2f(1280 / 3, 720 / 2));
	QuitText.setString("Quitter");
	QuitText.setFont(font);
	QuitText.setFillColor(sf::Color::Black);
	QuitText.setPosition(Vector2f(QuitButton.getGlobalBounds().left + QuitButton.getGlobalBounds().width / 2.2, QuitButton.getGlobalBounds().top + QuitButton.getGlobalBounds().height / 3));

	a_Button.setRadius(PlayButton.getLocalBounds().height / 3);
	a_Button.setPosition(PlayButton.getPosition().x + 20, PlayButton.getPosition().y + 18);
	A_ButtonTex->loadFromFile("Textures/A_Button.png");
	A_ButtonTex->setSmooth(true);
	a_Button.setTexture(A_ButtonTex);

	b_Button.setRadius(QuitButton.getLocalBounds().height / 3);
	b_Button.setPosition(QuitButton.getPosition().x + 20, QuitButton.getPosition().y + 18);
	B_ButtonTex->loadFromFile("Textures/B_Button.png");
	B_ButtonTex->setSmooth(true);
	b_Button.setTexture(B_ButtonTex);
}

void DrawMainMenu(sf::RenderWindow &win, Text fps) {
	win.draw(Title);
	win.draw(PlayButton);
	win.draw(QuitButton);
	win.draw(PlayText);
	win.draw(QuitText);
	win.draw(a_Button);
	win.draw(b_Button);
	win.draw(fps);
	win.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280,720), "I LOVE TANKS!", sf::Style::Default, settings);	//Creer une fenetre appelé "SFML Works" de taille 200x200)
	window.setVerticalSyncEnabled(true);

	sf::Clock Clock;

	sf::Time appStart = Clock.getElapsedTime();
	sf::Time frameStart = Clock.getElapsedTime();
	sf::Time prevFrameStart = Clock.getElapsedTime();

	float fps[4] = { 0.f, 0.f, 0.f, 0.f };
	int step = 0;
	int every = 10;

	sf::Text fpsText;
	sf::Text EndText;
	EndText.setPosition(1280/2, 720/3);
	EndText.setFont(font);
	EndText.setStyle(sf::Text::Italic);
	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::Red);

	initMenu();
	initMap();

	float squareSpeed1 = 1, squareSpeed2 = 1;
	float xR1 = 0, yR1 = 0, xL1 = 0, yL1 = 0, xR2 = 0, yR2 = 0, xL2 = 0, yL2 = 0, Trig1 = 0, Trig2 = 0; //Inputs J1 J2
	bool Fire1 = false, Fire2 = false, EndGame = false, MainMenu = true;


	while (window.isOpen())																			//tout le temps.
	{
		sf::Event event;
		if (every == 0)
		{
			fpsText.setString("FPS: " + std::to_string(fps[(step - 1) % 4]));
			every = 100;
		}
		every--;
		frameStart = Clock.getElapsedTime();

		while (MainMenu)
		{
			window.clear();
			if (every == 0)
			{
				fpsText.setString("FPS: " + std::to_string(fps[(step - 1) % 4]));
				every = 100;
			}
			every--;
			frameStart = Clock.getElapsedTime();

			DrawMainMenu(window, fpsText); //MainMenu

			fps[step % 4] = 1.0 / (frameStart - prevFrameStart).asSeconds();
			prevFrameStart = frameStart;
			step++;

			window.pollEvent(event);
			if (event.type == sf::Event::JoystickButtonReleased){
				if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 0)
					MainMenu = false;
				if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 1){
					window.close();
					MainMenu = false;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				MainMenu = false;
				window.close();
			}
		}

		if ((Objects[0]->destroyed || Objects[1]->destroyed) && !EndGame)
		{
			Objects[0]->destroyed ? EndText.setFillColor(sf::Color(0x5A94FFff)) : EndText.setFillColor(sf::Color(0xFF5245ff));
			Objects[0]->destroyed ? EndText.setString("	   Joueur Bleu gagne !\n Press R to Retry, Q to Quit") : EndText.setString("    Joueur Rouge gagne !\n Press R to Retry, Q to Quit");
			FloatRect TextRect = EndText.getLocalBounds();
			EndText.setOrigin(TextRect.left + TextRect.width / 2, TextRect.top + TextRect.height / 2);
			EndGame = true;
		}

																					//recup les event clavier/pad	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::I)
					printf("Instant fps %f\n", fps[(step - 1) % 4]);

				if (event.key.code == sf::Keyboard::F)
					printf("fps %f\n", 0.25*(fps[0] + fps[1] + fps[2] + fps[3]));

				if (event.key.code == sf::Keyboard::R && EndGame) {
					EndGame = false;
					Objects.clear();
					window.clear();
					initMap();
					squareSpeed1 = 1, squareSpeed2 = 1;
					xR1 = 0, yR1 = 0, xL1 = 0, yL1 = 0, xR2 = 0, yR2 = 0, xL2 = 0, yL2 = 0, Trig1 = 0, Trig2 = 0;
					Fire1 = false, Fire2 = false, EndGame = false;
					EndText.setString("");
				}

				if (event.key.code == sf::Keyboard::Q && EndGame)
					window.close();

				/*if (event.key.code == sf::Keyboard::Space)
					drawProjectile(window);*/
			}

			if (event.type == sf::Event::JoystickMoved) //Joystick Input Update
			{
				if (event.joystickMove.joystickId == 0)
				{
					if (event.joystickMove.axis == sf::Joystick::Axis::X)
						xR1 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::Y)
						yR1 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::U)
						xL1 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::V)
						yL1 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::Z)
						Trig1 = event.joystickMove.position;
				}

				if (event.joystickMove.joystickId == 1)
				{
					if (event.joystickMove.axis == sf::Joystick::Axis::X)
						xR2 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::Y)
						yR2 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::U)
						xL2 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::V)
						yL2 = event.joystickMove.position;
					if (event.joystickMove.axis == sf::Joystick::Axis::R)
						Trig2 = event.joystickMove.position;
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}


		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
				squareSpeed -= 0.3f;*/

		if (xR1 > 20 || xR1 < -20 || yR1 > 20 || yR1 < -20) //Mouvement J1
		{
			if (squareSpeed1 < 2)
				squareSpeed1 += 0.05f;
			SquarePos1.x += (xR1 / 100) * squareSpeed1;
			SquarePos1.y += (yR1 / 100) * squareSpeed1;
			//Possible fonction de rotation du tank
		}
		else
			if (squareSpeed1 > 0)
				squareSpeed1 -= 0.3f;

		if (xR2 > 20 || xR2 < -20 || yR2 > 20 || yR2 < -20) //Mouvement J2
		{
			if (squareSpeed2 < 2)
				squareSpeed2 += 0.05f;
			SquarePos2.x += (xR2 / 100) * squareSpeed1;
			SquarePos2.y += (yR2 / 100) * squareSpeed1;
			//Possible fonction de rotation du tank
		}
		else
			if (squareSpeed2 > 0)
				squareSpeed2 -= 0.3f;

		if ((Trig1 > 80 || Trig1 < -80) && !Fire1) //Shoot J1
		{
			Fire1 = true;
			drawProjectile(window, 0);
		}
		else if ((-10 < Trig1 && Trig1 < 10) && Fire1 && !Objects[0]->destroyed)
			Fire1 = false;

		if ((Trig2 > 80 || Trig2 < -80) && !Fire2) //Shoot J2
		{
			Fire2 = true;
			drawProjectile(window, 1);
		}
		else if ((-80 < Trig2 < 80) && Fire2 && !Objects[1]->destroyed)
			Fire2 = false;

		window.clear();																				//Nettoie la frame
		drawMap(window);
		window.draw(fpsText);
		window.draw(EndText);

			
		for (int i = 0; i < 2; i++)
		{
			switch (i)
			{
			case 0:
				if (Objects[i]->playable && Objects[i]->sprite != nullptr)
				{
					Objects[i]->sprite->setPosition(SquarePos1.x, SquarePos1.y);
					drawCible(window, xL1, yL1, i);
					LastPos[i] = Objects[i]->sprite->getPosition();
					Objects[i]->box = Objects[i]->sprite->getGlobalBounds();
				}

				break;

			case 1:
				if (Objects[i]->playable && Objects[i]->sprite != nullptr)
				{
					Objects[1]->sprite->setPosition(SquarePos2.x, SquarePos2.y);
					drawCible(window, xL2, yL2, i);
					LastPos[i] = Objects[i]->sprite->getPosition();
					Objects[i]->box = Objects[i]->sprite->getGlobalBounds();
				}
				break;

			default:
				break;
			}
		}

		for (int i = 0; i < Objects.size(); i++) {
			Objects[i]->Move();
		}

		for (int i = 0; i < Objects.size(); i++)
		{
			if (i != 0 && Objects[0]->box.intersects(Objects[i]->box) && Objects[0]->playable)
			{
				if (!Objects[i]->movable || Objects[i]->playable)	//Cas: Tank1 vs Wall
				{
					SquarePos1 = LastPos[0];
					Objects[0]->sprite->setPosition(LastPos[0]);
				}
				else						//Cas: Tank vs Proj
				{
					Objects.erase(Objects.begin()+i);
					Objects[0]->Destroyed(Objects, 0);
					Fire1 = true;
					break;
				}
			}

			if (i != 1 && Objects[1]->box.intersects(Objects[i]->box) && i != 1 && Objects[1]->playable)
			{
				if (!Objects[i]->movable || Objects[i]->playable)	//Cas: Tank1 vs Wall
				{
					SquarePos2 = LastPos[1];
					Objects[1]->sprite->setPosition(LastPos[1]);
				}
				else						//Cas: Tank vs Proj
				{
					Objects.erase(Objects.begin() + i);
					Objects[1]->Destroyed(Objects, 1);
					Fire2 = true;
					break;
				}
			}

			
			for (int j = 2; j < Objects.size(); j++)
			{
				if (i != j && i != 1 && i != 0 && Objects[i]->box.intersects(Objects[j]->box))
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
