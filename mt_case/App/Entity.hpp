#pragma once

#include <SFML/Graphics.hpp>

class Game;

using namespace sf;

enum EntityState
{
	ES_IDLE,
	ES_RUNNING,
	ES_FALLING,
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

	bool applyGravity = false;

	float pixelX = 0.0;
	float pixelY = 0.0;

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

	void update(double dt) {
		rx += dx;
		if (dx > 0) {
			while (rx > 1) { 
				if (!willCollide(cx+1, cy)) {
					cx++;
					rx--;
				}
				else {
					dx = 0;
					rx = 0.9;
					break;
				}
			}
		}
		else if (dx < 0) {
			while (rx < 0) {
				if (!willCollide(cx-1, cy)) {
					cx--;
					rx++;
				}
				else {
					dx = 0;
					rx = 0.1;
					break;
				}
			}
		}
		dx *= 0.92;
		if (abs(dx) < 0.05)
			dx = 0;

		if (applyGravity) dy += gy;

		ry += dy;
		if (dy > 0) {
			while (ry > 1)
			{
				if (!willCollide(cx, cy + 1)) {
					cy++;
					ry--;
				}
				else {
					dy = 0;
					ry = 0.99;
					break;
				}
			}
		}
		else if (dy < 0) {
			while (ry < 0) {
				if (!willCollide(cx, cy - 1)) {
					cy--;
					ry++;
				}
				else {
					dy = 0;
					ry = 0.01;
					break;
				}
			}
		}
		if (dy >= 2.0f)
			dy = 2.0f;

		if (dx == 0 && dy == 0 && getState() != ES_IDLE)
			changeState(ES_IDLE);

		syncCoord();
	}

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

	bool willCollide(int cx, int cy);
};