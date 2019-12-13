#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>
#include <functional>

#include "Lib.hpp"
#include "Particle.h"
#include "Action.hpp"
#include <Box2D/Box2D.h>

#include "Entity.hpp"

using namespace sf;

class Game {
public:
	std::vector<Particle*> pvec;
	std::vector<Entity*> evec;
	std::vector<Vector2i> platforms;

	sf::Font * font;
	static Game * me;
	Entity * player;

	Game() {

	}

	void init();
	void update(double dt);
	void draw(RenderWindow & win);
	bool willCollide(Entity * end, int cx, int cy);
	void togglePlatform(int cx, int cy);
};
