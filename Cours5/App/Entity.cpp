#include "Entity.hpp"

void Entity::_draw(sf::RenderWindow & win) {
	if (sprite != nullptr)
		win.draw(*sprite);
}

void Entity::Destroyed(std::vector<Entity*> Objects, int player) {
	delete Objects[player]->sprite;
	Objects[player]->box = FloatRect(-10, -10, 0, 0);
	Objects[player]->sprite = nullptr;
	destroyed = true;
}

void Entity::HittingUpdate() {
	if (hitted && !destroyed)
	{
		frame++;
		if (frame % 15 == 0)
		{
			sprite->getFillColor().a == 255 ? sprite->setFillColor(sf::Color(255, 255, 255, 120)) : sprite->setFillColor(sf::Color(255, 255, 255, 255));

		}
		if (frame == 180)
		{
			sprite->setFillColor(sf::Color(255, 255, 255, 255));
			frame = 0;
			hitted = false;
		}

	}
}
