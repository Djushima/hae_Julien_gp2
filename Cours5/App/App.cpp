// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include <direct.h>
#include <iostream>
#include <thread>
#include "Lib.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "Anims.hpp"
#include "Particle.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

static std::vector<Entity*> Objects;
static std::vector<Projectile*> ProjectileTab;
static std::vector<Animation*> AnimTab;
static std::vector<Particle*> ParticleTab;
static std::vector<Sprite> ImpactTab;
static std::vector<Entity*> LifeTab;
static std::vector<float> LastCible{ 45, 45 };
static std::vector<float> LastRot{ 45, 45 };
static std::vector<Vector2f> LastPos{Vector2f(640,360) , Vector2f(0,0)};
static Vector2f SquarePos1, SquarePos2;
static const double PI = 3.141592653589793238463;


RectangleShape bg, beac;
CircleShape a_Button, b_Button;
Text Title, PlayText, QuitText, CreditText;
Sprite Tank1, Tank2;
Texture *A_ButtonTex = new Texture(), *B_ButtonTex = new Texture(), *BG = new Texture(), *Border = new Texture(),
		*Bullet1 = new Texture(), *Bullet2 = new Texture(), *tank1Tex = new Texture(), *tank2Tex = new Texture(),
		*CanonTank1Tex = new Texture(), *CanonTank2Tex = new Texture(), *Tank1UI = new Texture(), *Tank2UI = new Texture(),
		*WallTex = new Texture(), *WoodTex = new Texture(), *Burn = new Texture(), *Smoke = new Texture(), *BeaconTex = new Texture();
Font font;
sf::Sound HitSFX1, HitSFX2, ExplosionSFX1, ExplosionSFX2, ShotSFX1, ShotSFX2, BounceSFX;
sf::Music BGM;
sf::SoundBuffer HitSound, ExplosionSound, ShotSound, BounceSound;

enum GameState {
	MainMenu,
	Playing,
	Quit,
};
static GameState State = MainMenu;


RectangleShape* initSquareRender(int x, int y) {
	auto Square = new RectangleShape(Vector2f(x,y));
	return Square;
}

void initSound() {
	if (!HitSound.loadFromFile("Sound/Hit.wav"))
		printf("Error Load sound HIT");
	if (!ShotSound.loadFromFile("Sound/Shot1.wav"))
		printf("Error Load sound HIT");
	if (!ExplosionSound.loadFromFile("Sound/Explosion.wav"))
		printf("Error Load sound HIT");
	if (!BounceSound.loadFromFile("Sound/Bounce.wav"))
		printf("Error Load sound HIT");
	if (!BGM.openFromFile("Sound/BGM.wav"))
		printf("Error Load sound HIT");
	else
		BGM.setLoop(true);
}

void initTextures() {
	if (!Border->loadFromFile("Textures/Wall.png"))
		printf("Wall Texture Error Load");
	Border->setSmooth(true);
	Border->setRepeated(true);
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
	if (!tank1Tex->loadFromFile("Textures/Red tank -canon.png"))
		printf("Tank1 Texture Error Load");
	tank1Tex->setSmooth(true);
	if (!tank2Tex->loadFromFile("Textures/Blue tank -canon.png"))
		printf("Tank2 Texture Error Load");
	tank2Tex->setSmooth(true);
	if (!CanonTank1Tex->loadFromFile("Textures/Canon Rouge.png"))
		printf("Tank2 Texture Error Load");
	CanonTank1Tex->setSmooth(true);
	if (!CanonTank2Tex->loadFromFile("Textures/Canon Bleu.png"))
		printf("Tank2 Texture Error Load");
	CanonTank2Tex->setSmooth(true);
	if (!Smoke->loadFromFile("Textures/Smoke.png"))
		printf("Smoke Texture Error Load");
	Smoke->setSmooth(true);
	if (!WallTex->loadFromFile("Textures/Wall_Cube.jpg"))
		printf("WallCube Texture Error Load");
	WallTex->setSmooth(true);
	if (!WoodTex->loadFromFile("Textures/wood_Crate.jpg"))
		printf("WoodCube Texture Error Load");
	WoodTex->setSmooth(true);
	if (!Burn->loadFromFile("Textures/Burned.png"))
		printf("Burn Texture Error Load");
	Burn->setSmooth(true);
	if (!Tank1UI->loadFromFile("Textures/Red tank.png"))
		printf("Tank1UI Texture Error Load");
	Tank1UI->setSmooth(true);
	if (!Tank2UI->loadFromFile("Textures/Blue tank.png"))
		printf("Tank2UI Texture Error Load");
	Tank2UI->setSmooth(true);
	if (!BeaconTex->loadFromFile("Textures/Beacon.png"))
		printf("Beacon Texture Error Load");
	BeaconTex->setSmooth(true);
}

void initMap() {
	auto Char1 = new Entity(
		initSquareRender(60, 40),
		Vector2f(SquarePos1.x = 425, SquarePos1.y = 360));
	Char1->sprite->setTexture(tank1Tex);
	Char1->sprite->setOrigin(Vector2f(30, 20));
	Char1->movable = true;
	Char1->playable = true;
	Objects.push_back(Char1);

	auto Char2 = new Entity(
		initSquareRender(60, 40),
		Vector2f(SquarePos2.x = 850, SquarePos2.y = 360));
	Char2->sprite->setTexture(tank2Tex); 
	Char2->sprite->setOrigin(Vector2f(30, 20));
	Char2->movable = true;
	Char2->playable = true;
	Objects.push_back(Char2);

	auto NBorder = new Entity(
		initSquareRender(1280, 50),
		Vector2f(0, 0));
	NBorder->sprite->setTexture(Border);
	NBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	NBorder->box = NBorder->sprite->getGlobalBounds();
	Objects.push_back(NBorder);

	auto SBorder = new Entity(
		initSquareRender(1280, 50),
		Vector2f(0, 670));
	SBorder->sprite->setTexture(Border);
	SBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	SBorder->box = SBorder->sprite->getGlobalBounds();
	Objects.push_back(SBorder);

	auto EBorder = new Entity(
		initSquareRender(620, 50),
		Vector2f(1280, 50));
	EBorder->sprite->setTexture(Border);
	EBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	EBorder->sprite->setRotation(90);
	EBorder->box = EBorder->sprite->getGlobalBounds();
	Objects.push_back(EBorder);

	auto WBorder = new Entity(
		initSquareRender(620, 50),
		Vector2f(0, 50));
	WBorder->sprite->setTexture(Border);
	WBorder->sprite->setTextureRect(IntRect(0, 0, 1280, 128));
	WBorder->sprite->setRotation(90);
	WBorder->sprite->setOrigin(0, 50);
	WBorder->box = WBorder->sprite->getGlobalBounds();
	Objects.push_back(WBorder);

	srand(time(NULL));
	int seed = rand() % 3;
	switch (seed){
	case 0:
	{
		auto Wall = new Entity(initSquareRender(150, 150), Vector2f(565, 285));
		Wall->sprite->setTexture(WallTex);
		Wall->sprite->setOutlineThickness(1);
		Wall->sprite->setOutlineColor(sf::Color::Black);
		Wall->box = Wall->sprite->getGlobalBounds();
		Objects.push_back(Wall);
		break;
	}
	case 1:
	{
		for (int i = 0; i < 7; i++)
		{
			auto Wall = new Entity(initSquareRender(100, 100), Vector2f(590, 310));
			Wall->sprite->setTexture(WallTex);
			Wall->sprite->setOutlineThickness(1);
			Wall->sprite->setOutlineColor(sf::Color::Black);
			switch (i)
			{
			case 1:
				Wall->sprite->setPosition(270, 310);
				break;

			case 2:
				Wall->sprite->setPosition(910, 310);
				break;

			case 3:
				Wall->sprite->setPosition(430, 150);
				break;

			case 4:
				Wall->sprite->setPosition(750, 150);
				break;

			case 5:
				Wall->sprite->setPosition(750, 470);
				break;

			case 6:
				Wall->sprite->setPosition(430, 470);
				break;

			default:
				break;
			}
			Wall->box = Wall->sprite->getGlobalBounds();
			Objects.push_back(Wall);
		}
		break;
	}
	default:
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				auto Wall = new Entity(initSquareRender(50, 50), Vector2f(640, 360));
				Wall->sprite->setPosition(i * 236 +143, j * 155+103);
				Wall->sprite->setTexture(WallTex);
				Wall->sprite->setOutlineThickness(1);
				Wall->sprite->setOutlineColor(sf::Color::Black);
				Wall->box = Wall->sprite->getGlobalBounds();
				Objects.push_back(Wall);
			}
		}
		break;
	}}

	seed = rand() % 30 + 20;
	for (int i = 0; i < seed; i++)
	{
		auto DestructWall = new Entity(initSquareRender(25, 25), Vector2f(640, 360));
		DestructWall->destroyable = true;
		DestructWall->sprite->setTexture(WoodTex);
		DestructWall->sprite->setOutlineThickness(1);
		DestructWall->sprite->setOutlineColor(sf::Color::Black);
	restart:
		DestructWall->sprite->setPosition(rand() % 1180 + 100, rand() % 620 + 100);
		DestructWall->box = DestructWall->sprite->getGlobalBounds();
		for (int j = 0; j < Objects.size(); j++)
		{
			if (DestructWall->box.intersects(Objects[0]->sprite->getGlobalBounds()) || DestructWall->box.intersects(Objects[1]->sprite->getGlobalBounds()))
				goto restart;
			if (DestructWall->box.intersects(Objects[j]->box))
				goto restart;
		}
		Objects.push_back(DestructWall);
	}
}

void initMenu() {
	font.loadFromFile("earthorbiter.ttf");
	Title.setString("Call of Tanks:\n    1v1 me Bro");
	Title.setFont(font);
	Title.setCharacterSize(50);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(430, 120);

	PlayText.setString("Press A to Play");
	PlayText.setFont(font);
	PlayText.setFillColor(sf::Color::Green);
	PlayText.setPosition(200, 480);

	QuitText.setString("Press B to Quit");
	QuitText.setFont(font);
	QuitText.setFillColor(sf::Color::Red);
	QuitText.setPosition(840, 480);

	a_Button.setRadius(30);
	a_Button.setPosition(PlayText.getPosition().x + 105, PlayText.getPosition().y + 60);
	A_ButtonTex->loadFromFile("Textures/A_Button.png");
	A_ButtonTex->setSmooth(true);
	a_Button.setTexture(A_ButtonTex);

	b_Button.setRadius(30);
	b_Button.setPosition(QuitText.getPosition().x + 105, QuitText.getPosition().y + 60);
	B_ButtonTex->loadFromFile("Textures/B_Button.png");
	B_ButtonTex->setSmooth(true);
	b_Button.setTexture(B_ButtonTex);

	bg.setSize(Vector2f(1280, 720));
	bg.setTexture(BG);
	auto k = 256 * 8;
	bg.setTextureRect(IntRect(0, 0, k, k));

	Tank1.setTexture(*Tank1UI);
	Tank2.setTexture(*Tank2UI);
	Tank1.setPosition(PlayText.getPosition().x + 230, PlayText.getPosition().y - 60);
	Tank1.setRotation(180);
	Tank2.setPosition(QuitText.getPosition().x + 230, QuitText.getPosition().y - 60);
	Tank2.setRotation(180);

	CreditText.setString("Division Blade by Schematist: http://www.schematistmusic.com / Music promoted by https://www.free-stock-music.com \n				Creative Commons Attribution 3.0 Unported License https://creativecommons.org/licenses/by/3.0/");
	CreditText.setCharacterSize(12);
	CreditText.setFont(font);
	CreditText.setPosition(200, 680);
	CreditText.setFillColor(sf::Color::White);
}

void initGameUI() {
	for (int i = 0; i < 3; i++)
	{
		Entity *vie = new Entity(
			initSquareRender(50, 33.3),
			Vector2f(SquarePos1.x = 425, SquarePos1.y = 360));
		vie->sprite->setTexture(Tank1UI);
		vie->sprite->setOrigin(25, 16.65);
		vie->sprite->setPosition(80 + i * 100, 695);
		LifeTab.push_back(vie);
	}

	for (int i = 0; i < 3; i++)
	{
		Entity *vie = new Entity(
			initSquareRender(50, 33.3),
			Vector2f(SquarePos1.x = 425, SquarePos1.y = 360));
		vie->sprite->setTexture(Tank2UI);
		vie->sprite->setOrigin(25, 16.65);
		vie->sprite->setPosition(1000 + i * 100, 25);
		LifeTab.push_back(vie);
	}
}

void DrawMainMenu(sf::RenderWindow &win) {
	win.draw(bg);
	win.draw(Title);
	win.draw(PlayText);
	win.draw(QuitText);
	win.draw(a_Button);
	win.draw(b_Button);
	win.draw(Tank1);
	win.draw(Tank2);
	win.draw(CreditText);
	win.display();
}

void drawGameUi(sf::RenderWindow &win) {
	for (int i = 0; i < LifeTab.size(); i++)
	{
		LifeTab[i]->_draw(win);
	}
}

void drawMap(sf::RenderWindow &win) {
	win.draw(bg);
	for (int i = 0; i < Objects.size(); i++)
		Objects[i]->_draw(win);
}

void drawCible(sf::RenderWindow &win, float X, float Y, int player)
{
	sf::Shape *Canon = initSquareRender(60, 40);
	player == 0 ? Canon->setTexture(CanonTank1Tex) : Canon->setTexture(CanonTank2Tex);
	Canon->setOrigin(27, 20);
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
		Vector2f(Objects[player]->sprite->getPosition().x + cos(angle) * 48, Objects[player]->sprite->getPosition().y + sin(angle) * 48),
		player);
	player == 0 ? Proj->sprite->setTexture(Bullet1) : Proj->sprite->setTexture(Bullet2);
	Proj->sprite->setOrigin(Vector2f(5, 0));
	Objects.push_back(Proj);
}

void InitParticles(Entity *parent, prtType type, int quantity)
{
	srand(time(NULL));
	int maxPrt = rand() % quantity + 20;
	int i = 0;
	while (i != maxPrt)
	{
		i++;
		sf::Shape *shp = new CircleShape(8, 64);
		Vector2f spd;
		float life = rand() %90 +30;
		sf::Color clr;
		switch (type)
		{
		case Eplode:
			spd = Vector2f((rand() % 10 - 5) / 1.33f, (rand() % 10 - 5) / 1.33f);
			shp->setPosition(parent->sprite->getPosition());
			clr = sf::Color::Red;
			break;
		}
		Particle *prt = new Particle(shp, spd, life, clr, Smoke, type);
		ParticleTab.push_back(prt);
	}
}

void InitImpact(Entity *parent)
{
	Sprite *Impact = new Sprite(*Burn);
	Impact->setOrigin(Vector2f(490, 490));
	Impact->setPosition(Vector2f(parent->sprite->getPosition().x, parent->sprite->getPosition().y));
	Impact->setScale(0.08, 0.08);
	ImpactTab.push_back(*Impact);
}

void Beacon(sf::RenderWindow &win)
{
	if (beac.getTexture() != BeaconTex)
	{
		beac.setSize(Vector2f(1600, 1600));
		beac.setTexture(BeaconTex);
		beac.setFillColor(sf::Color(255, 255, 255, 120));
		beac.setOrigin(800, 800);
		beac.setPosition(640, 360);
	}
	win.draw(beac);
	beac.setRotation(beac.getRotation() + 2);		
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280,720), "Call of Tanks", sf::Style::Default, settings);	
	window.setVerticalSyncEnabled(true);

	sf::Clock Clock;
	sf::Time frameStart = Clock.getElapsedTime();
	sf::Time prevFrameStart = Clock.getElapsedTime();

	sf::Text EndText;
	EndText.setPosition(320, 180);
	EndText.setFont(font);
	EndText.setCharacterSize(40);
	EndText.setOutlineColor(sf::Color::Black);
	EndText.setOutlineThickness(1);
	EndText.setStyle(sf::Text::Italic);

	initSound();
	initTextures();
	initMenu();
	initMap();
	initGameUI();

	int frame = 0, shakeRate = 2, shakeDur = 30, knockbackRate =0;
	float squareSpeed1 = 1, squareSpeed2 = 1, FireCount1 =0, FireCount2 =0;
	float xR1 = 0, yR1 = 0, xL1 = 0, yL1 = 0, xR2 = 0, yR2 = 0, xL2 = 0, yL2 = 0, Trig1 = 0, Trig2 = 0; //Inputs J1 J2
	bool Fire1 = false, Fire2 = false, EndGame = false, shake = false;
	Vector2f tank1Dir, tank2Dir;
	Vector2i baseScreenPos;

	baseScreenPos = window.getPosition();
	BGM.play();


	while (window.isOpen())																			//tout le temps.
	{
		sf::Event event;
		frameStart = Clock.getElapsedTime();

		switch (State)
		{
		case MainMenu:
			window.clear();
			DrawMainMenu(window); //MainMenu
			drawMap(window);

			window.pollEvent(event);
			if (event.type == sf::Event::JoystickButtonReleased) {
				if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 0)
					State = Playing;
				if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 1) {
					window.close();
					State = Quit;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
				State = Quit;
			}
			break;


		case Playing:
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::JoystickButtonReleased)
				{
					if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 3 && EndGame) {
						EndGame = false;
						Objects.clear();
						LifeTab.clear();
						window.clear();
						initMap();
						initGameUI();
						squareSpeed1 = 1, squareSpeed2 = 1;
						xR1 = 0, yR1 = 0, xL1 = 0, yL1 = 0, xR2 = 0, yR2 = 0, xL2 = 0, yL2 = 0, Trig1 = 0, Trig2 = 0;
						Fire1 = false, Fire2 = false, EndGame = false;
						EndText.setString("");
					}

					if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 1 && EndGame)
						window.close();
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
						if (event.joystickMove.axis == sf::Joystick::Axis::Z)
							Trig2 = event.joystickMove.position;
					}
				}

				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (Objects[0]->Life != 0)
			{
				LastPos[0] = Objects[0]->sprite->getPosition();
				LastRot[0] = Objects[0]->sprite->getRotation();
			}
			if (Objects[1]->Life != 0)
			{
				LastRot[1] = Objects[1]->sprite->getRotation();
				LastPos[1] = Objects[1]->sprite->getPosition();
			}



			if (xR1 > 20 || xR1 < -20 || yR1 > 20 || yR1 < -20) //Mouvement J1
			{
				if (squareSpeed1 < 2)
					squareSpeed1 += 0.05f;
				SquarePos1.x += (xR1 / 100) * squareSpeed1;
				SquarePos1.y += (yR1 / 100) * squareSpeed1;
				tank1Dir = Vector2f(xR1, yR1);
			}
			else
				if (squareSpeed1 > 0)
					squareSpeed1 -= 0.3f;

			if (xR2 > 20 || xR2 < -20 || yR2 > 20 || yR2 < -20) //Mouvement J2
			{
				if (squareSpeed2 < 2)
					squareSpeed2 += 0.05f;
				SquarePos2.x += (xR2 / 100) * squareSpeed2;
				SquarePos2.y += (yR2 / 100) * squareSpeed2;
				tank2Dir = Vector2f(xR2, yR2);
			}
			else
				if (squareSpeed2 > 0)
					squareSpeed2 -= 0.3f;

			if ((Trig1 > 80 || Trig1 < -80) && !Fire1) //Shoot J1
			{
				Vector2f Pos1 = Objects[0]->sprite->getPosition();
				Fire1 = true;
				drawProjectile(window, 0);
				Animation *shot1 = new Animation(animName::Shot, Objects[0], LastCible[0]);
				AnimTab.push_back(shot1);
				Objects[0]->sprite->setPosition(Pos1.x - cos(LastCible[0]) * 5, Pos1.y - sin(LastCible[0]) * 5);
				ShotSFX1.setBuffer(ShotSound);
				ShotSFX1.play();
			}
			else if ((-10 < Trig1 && Trig1 < 10) && Fire1 && !Objects[0]->destroyed)
			{
				FireCount1++;
				if (FireCount1 >= 15)
				{
					Fire1 = false;
					FireCount1 = 0;
				}
			}

			if ((Trig2 > 80 || Trig2 < -80) && !Fire2) //Shoot J2
			{
				Vector2f Pos2 = Objects[1]->sprite->getPosition();
				Fire2 = true;
				drawProjectile(window, 1);
				Animation *shot2 = new Animation(animName::Shot, Objects[1], LastCible[1]);
				AnimTab.push_back(shot2);
				Objects[1]->sprite->setPosition(Pos2.x - cos(LastCible[1]) * 5, Pos2.y - sin(LastCible[1]) * 5);
				ShotSFX2.setBuffer(ShotSound);
				ShotSFX2.play();
			}
			else if ((-80 < Trig2 < 80) && Fire2 && !Objects[1]->destroyed)
			{
				FireCount2++;
				if (FireCount2 >= 15)
				{
					Fire2 = false;
					FireCount2 = 0;
				}
			}

			window.clear();
			drawMap(window);
			window.draw(EndText);
			drawGameUi(window);

			for (int i = 0; i < 2; i++)
			{
				switch (i)
				{
				case 0:
					if (Objects[i]->playable && Objects[i]->Life != 0)
					{
						Objects[i]->sprite->setRotation(atan2(tank1Dir.y, tank1Dir.x) * (180 / PI)); //collisions avec rotation non opti
						Objects[i]->sprite->setPosition(SquarePos1.x, SquarePos1.y);
						drawCible(window, xL1, yL1, i);
						Objects[i]->box.top = Objects[i]->sprite->getPosition().y - 20;
						Objects[i]->box.left = Objects[i]->sprite->getPosition().x - 20;
						Objects[i]->box.height = 40;
						Objects[i]->box.width = 40;
					}

					break;

				case 1:
					if (Objects[i]->playable && Objects[i]->Life != 0)
					{
						Objects[i]->sprite->setRotation(atan2(tank2Dir.y, tank2Dir.x) * (180 / PI)); //collisions avec rotation non opti
						Objects[1]->sprite->setPosition(SquarePos2.x, SquarePos2.y);
						drawCible(window, xL2, yL2, i);
						Objects[i]->box.top = Objects[i]->sprite->getPosition().y - 20;
						Objects[i]->box.left = Objects[i]->sprite->getPosition().x - 20;
						Objects[i]->box.height = 40;
						Objects[i]->box.width = 40;
					}
					break;

				default:
					break;
				}
			}

			for (int i = 0; i < Objects.size(); i++) {
				Objects[i]->Move();
				Objects[i]->HittingUpdate();
			}

			for (int i = 0; i < Objects.size(); i++)
			{
				if (i != 0 && Objects[0]->box.intersects(Objects[i]->box) && Objects[0]->playable)
				{
					if (!Objects[i]->movable || Objects[i]->playable)	//Cas: Tank1 vs Wall
					{
						SquarePos1 = LastPos[0];
						Objects[0]->sprite->setPosition(LastPos[0]);
						Objects[0]->sprite->setRotation(LastRot[0]);
					}
					else 						//Cas: Tank1 vs Proj
					{
						InitImpact(Objects[i]);
						Animation *hit = new Animation(animName::Hit, Objects[i], LastCible[0]);
						AnimTab.push_back(hit);
						HitSFX1.setBuffer(HitSound);
						HitSFX1.play();
						if (!Objects[0]->hitted)
						{
							shake = true;
							shakeRate = 3;
							shakeDur = 30;
							Objects[0]->hitted = true;
							Objects[0]->Life -= 1;
							Animation *boom = new Animation(animName::Explosion, LifeTab[Objects[0]->Life], LastCible[0]);
							AnimTab.push_back(boom);
							InitImpact(LifeTab[Objects[0]->Life]);
							LifeTab.erase(LifeTab.begin() + Objects[0]->Life);
							if (Objects[0]->Life <= 0)
							{
								shakeRate = 2;
								shakeDur = 60;
								InitParticles(Objects[0], prtType::Eplode, 30);
								Animation *boom = new Animation(animName::Explosion, Objects[0], LastCible[0]);
								AnimTab.push_back(boom);
								Objects[0]->Destroyed(Objects, 0);
								Fire1 = true;
								ExplosionSFX1.setBuffer(ExplosionSound);
								ExplosionSFX1.play();
							}
						}
						Objects.erase(Objects.begin() + i);
						break;
					}
				}

				if (i != 1 && Objects[1]->box.intersects(Objects[i]->box) && i != 1 && Objects[1]->playable)
				{
					if (!Objects[i]->movable || Objects[i]->playable)	//Cas: Tank2 vs Wall
					{
						SquarePos2 = LastPos[1];
						Objects[1]->sprite->setPosition(LastPos[1]);
						Objects[1]->sprite->setRotation(LastRot[1]);
					}
					else						//Cas: Tank2 vs Proj
					{
						InitImpact(Objects[i]);
						Animation *hit = new Animation(animName::Hit, Objects[i], LastCible[0]);
						AnimTab.push_back(hit);
						HitSFX2.setBuffer(HitSound);
						HitSFX2.play();
						if (!Objects[1]->hitted)
						{
							shake = true;
							shakeRate = 3;
							shakeDur = 30;
							Objects[1]->hitted = true;
							Objects[1]->Life -= 1;
							Animation *boom = new Animation(animName::Explosion, LifeTab[Objects[0]->Life + Objects[1]->Life], LastCible[0]);
							AnimTab.push_back(boom);
							InitImpact(LifeTab[Objects[0]->Life + Objects[1]->Life]);
							LifeTab.erase(LifeTab.begin() + Objects[0]->Life + Objects[1]->Life);
							if (Objects[1]->Life <= 0)
							{
								shakeRate = 2;
								shakeDur = 60;
								InitParticles(Objects[1], prtType::Eplode, 30);
								Animation *boom = new Animation(animName::Explosion, Objects[1], LastCible[0]);
								AnimTab.push_back(boom);
								Objects[1]->Destroyed(Objects, 1);
								Fire2 = true;
								ExplosionSFX2.setBuffer(ExplosionSound);
								ExplosionSFX2.play();
							}
						}
						Objects.erase(Objects.begin() + i);
						break;
					}
				}


				for (int j = 2; j < Objects.size(); j++)
				{
					if (i != j && i != 1 && i != 0 && Objects[i]->box.intersects(Objects[j]->box))
						if (Objects[i]->movable && !Objects[j]->movable) //Cas: Proj vs Wall = Rebond || Destroy
						{
							Projectile * proj = dynamic_cast<Projectile*>(Objects[i]);
							if (proj->Bounced || Objects[j]->destroyable)
							{
								HitSFX1.setBuffer(HitSound);
								HitSFX1.play();
								InitImpact(Objects[i]);
								Animation *hit = new Animation(animName::Hit, Objects[i], LastCible[0]);
								AnimTab.push_back(hit);
								Objects.erase(Objects.begin() + i);
								if (Objects[j]->destroyable)
									Objects.erase(Objects.begin() + j);
							}
							else
							{
								BounceSFX.setBuffer(BounceSound);
								BounceSFX.play();
								proj->Rebond(Objects[j]);
							}
							break;
						}
						else if (Objects[i]->movable && Objects[j]->movable) //Cas: Proj vs Proj = Destroy
						{
							InitImpact(Objects[i]);
							Animation *hit = new Animation(animName::Hit, Objects[i], LastCible[0]);
							AnimTab.push_back(hit);
							Objects.erase(Objects.begin() + i);
							Objects.erase(Objects.begin() + j - 1);
							break;
						}
				}

			}

			if ((Objects[0]->destroyed || Objects[1]->destroyed) && !EndGame)
			{
				Objects[0]->destroyed ? EndText.setFillColor(sf::Color(0x5A94FFff)) : EndText.setFillColor(sf::Color(0xFF5245ff));
				Objects[0]->destroyed ? EndText.setString("		  Blue Player Win !\n Press Y to Retry, B to Quit") : EndText.setString("		  Red Player Win !\n Press Y to Retry, B to Quit");
				EndGame = true;
			}

			for (int i = 0; i < ImpactTab.size(); i++)
			{
				window.draw(ImpactTab[i]);
				Color ImpactColor = ImpactTab[i].getColor();
				if (ImpactColor.a <= 0)
					ImpactTab.erase(ImpactTab.begin() + i);
				else
					ImpactTab[i].setColor(sf::Color(ImpactColor.r, ImpactColor.g, ImpactColor.b, ImpactColor.a - 2.125));
			}
			for (int i = 0; i < AnimTab.size(); i++)
			{
				window.draw(*AnimTab[i]->sprite);
				AnimTab[i]->update((frameStart - prevFrameStart).asSeconds());
				if (AnimTab[i]->completed) AnimTab.erase(AnimTab.begin() + i);
			}
			for (int i = 0; i < ParticleTab.size(); i++)
			{
				ParticleTab[i]->Update();
				if (ParticleTab[i]->Killed)
					ParticleTab.erase(ParticleTab.begin() + i);
				else
					ParticleTab[i]->draw(window);
			}

			if (shake)
			{
				frame++;
				if (frame % shakeRate == 0)
					if (shakeRate == 2)
						window.setPosition(Vector2i(baseScreenPos.x + rand() % 15 - 10, baseScreenPos.y + rand() % 15 - 10));
					else
						window.setPosition(Vector2i(baseScreenPos.x + rand() % 10 - 5, baseScreenPos.y + rand() % 10 - 5));
				if (frame > shakeDur)
				{
					frame = 0;
					shake = false;
					window.setPosition(baseScreenPos);
				}
			}

			Beacon(window);

			window.display();																			//Ca dessine et attends la vsync.
			break;

		case Quit:
			break;
		}
		prevFrameStart = frameStart;
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
