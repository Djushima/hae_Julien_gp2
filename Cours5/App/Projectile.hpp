#pragma once

#include "Entity.hpp"

class Projectile : public Entity {
private:
	const double PI = 3.141592653589793238463;
	const int speed = 5;
	Vector2f dir;
	float x, y;

public:
	bool Bounced;
	int Shooter;

	Projectile(float angle, sf::Shape *forme, Vector2f Pos, int shooter) :
		Entity(forme, Pos) {
		this->dir = Vector2f(cos(angle), sin(angle));
		this->Bounced = false;
		this->sprite->setRotation(angle * (180 / PI) - 90);
		this->x = this->sprite->getPosition().x;
		this->y = this->sprite->getPosition().y;
		this->movable = true;
		this->Shooter = shooter;
	}

	~Projectile() {
		if (dir != Vector2f(0, 0)) dir = Vector2f(0, 0);
	}

	void Move();

	void Rebond(Entity* Object2);

};