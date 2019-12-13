#pragma once

#include <SFML/Graphics.hpp>

class Game;

using namespace sf;

enum EntityState
{
	ES_IDLE,
	ES_WALKING,
	ES_RUNNING,
	ES_COVER,
};

class Entity {
public:
	EntityState state = ES_IDLE;
	static const int CELL_WIDTH = 16;

	int cx = 0; //Cell Position
	int cy = 0;

	float rx = 0.5; //Inside a Cell Position
	float ry = 0.5;

	float dx = 0.0f; //Movement
	float dy = 0.0f;

	float gy = 0.03;

	float pixelX = 0.0;
	float pixelY = 0.0;

	int stateLife = 0;

	sf::Shape * spr;

	Entity(sf::Shape * spr) {
		this->spr = spr;
	}

	void setPos(float crx, float cry) {
		rx += crx;
		ry += cry;
		updateCollision();
	}

	void setPosePixel(float pixelX, float pixelY) {
		cx = pixelX / CELL_WIDTH;
		cy = pixelY / CELL_WIDTH;

		rx = (pixelX - (cx*CELL_WIDTH)) / CELL_WIDTH;
		ry = (pixelY - (cy*CELL_WIDTH)) / CELL_WIDTH;

		syncCoord();
	}

	void update(double dt);

	void updateCollision() {

	}

	void syncCoord() {
		pixelX = cx * CELL_WIDTH + rx * CELL_WIDTH;
		pixelY = cy * CELL_WIDTH + ry * CELL_WIDTH;
		spr->setPosition(pixelX, pixelY);
	}

	void draw(sf::RenderWindow & win);

	EntityState getState() { return state; }
	void changeState(EntityState nes);
	void updateState();
	void updateControls();

	bool willCollide(int cx, int cy);
	std::string getStateName();
};