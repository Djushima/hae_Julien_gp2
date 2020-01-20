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
