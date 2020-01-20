#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
public:
	sf::Shape *sprite = nullptr;			//Rendu
	sf::FloatRect box;						//Collision
	bool movable = false, playable = false, destroyed = false;

	Entity(sf::Shape *forme, Vector2f Pos) {
		this->sprite = forme;
		this->sprite->setPosition(Pos);
		this->box = forme->getGlobalBounds();
	}

	~Entity() {
		if (sprite) delete sprite;
		sprite = nullptr;
	}

	void _draw(sf::RenderWindow &win);

	virtual void Move() {
	}

	virtual void Rebond(Entity* Object2) {
	}

	void Destroyed(std::vector<Entity*> Objects, int player);
};