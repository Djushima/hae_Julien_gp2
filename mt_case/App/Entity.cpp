#include "Entity.hpp"
#include "Game.hpp"

void Entity::draw(sf::RenderWindow & win) {

	sf::Text coords;
	coords.setFont(*Game::me->font);
	coords.setPosition(pixelX - 20, pixelY - 20);
	coords.setFillColor(sf::Color::Red);
	coords.setString(
		std::to_string(cx) + "," + std::to_string(cy) + " "
		+ std::to_string(rx) + "," + std::to_string(ry));

	win.draw(*spr);
	win.draw(coords);
}

void Entity::changeState(EntityState nes) {
	EntityState oldState = state;

	switch (oldState)
	{
	default:
		break;
	}

	switch (nes)
	{
	default:
		break;
	}

	state = nes;
}

bool Entity::willCollide(int cx, int cy) {
	return Game::me->willCollide(this, cx, cy);
}
