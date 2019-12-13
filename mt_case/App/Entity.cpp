#include "Entity.hpp"
#include "Game.hpp"


void Entity::update(double dt) {
	updateState();
	updateControls();
	rx += dx;
	if (dx > 0) {
		while (rx > 1) {
			if (!willCollide(cx + 1, cy)) {
				cx++;
				rx--;
			}
			else {
				dx = 0;
				rx = 0.99;
				break;
			}
		}
	}
	else if (dx < 0) {
		while (rx < 0) {
			if (!willCollide(cx - 1, cy)) {
				cx--;
				rx++;
			}
			else {
				dx = 0;
				rx = 0.01;
				break;
			}
		}
	}
	dx *= 0.92;
	if (abs(dx) < 0.03)
		dx = 0;


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
	dy *= 0.92;
	if (abs(dy) < 0.03)
		dy = 0;


	if (dx == 0 && dy == 0 && getState() != ES_IDLE && getState() != ES_COVER)
		changeState(ES_IDLE);

	syncCoord();
}

void Entity::draw(sf::RenderWindow & win) {

	sf::Text coords;
	coords.setFont(*Game::me->font);
	coords.setPosition(pixelX - 20, pixelY - 20);
	coords.setFillColor(sf::Color::Red);
	coords.setString(
		std::to_string(cx) + "," + std::to_string(cy) + " "
		+ std::to_string(rx) + "," + std::to_string(ry) + " " + getStateName());

	win.draw(*spr);
	win.draw(coords);
}

void Entity::changeState(EntityState nes) {
	if (nes == state)
		return;

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

	stateLife = 0;
	state = nes;
}

void Entity::updateState()
{
	switch (state)
	{
	case ES_IDLE:
		spr->setFillColor(sf::Color::White);

		if (willCollide(cx + 3, cy) ||
			willCollide(cx - 3, cy) ||
			willCollide(cx, cy + 3) ||
			willCollide(cx, cy - 3)) {

			if (stateLife == 60)
				changeState(ES_COVER);
		}
		break;

	case ES_WALKING:
		spr->setFillColor(sf::Color::Green);
		break;

	case ES_RUNNING:
		spr->setFillColor(sf::Color::Red);
		break;

	case ES_COVER:
		spr->setFillColor(sf::Color::Blue);
		break;

	default:
		break;
	}
	stateLife++;
};

void Entity::updateControls()
{
	auto max_lat_speed = 0.35;
	auto lat_acc = 0.035;


	switch (state)
	{
	case ES_IDLE:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))

			changeState(ES_WALKING);
		break;
	
	case ES_WALKING:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			changeState(ES_RUNNING);
		break;

	case ES_RUNNING:
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			if (state == ES_RUNNING)
				changeState(ES_WALKING);
		else
		{
			lat_acc *= 2;
			max_lat_speed *= 2;
		}
		break;

	case ES_COVER:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))

			changeState(ES_WALKING);
		break;

	default:
		break;
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		dx += lat_acc;
		if (dx > max_lat_speed) dx = max_lat_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		dx -= lat_acc;
		if (dx < -max_lat_speed) dx = -max_lat_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			dy += lat_acc;
			if (dy > max_lat_speed) dy = max_lat_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dy -= lat_acc;
			if (dy < -max_lat_speed) dy = -max_lat_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		setPosePixel(100, 600);
		dx = dy = 0.0f;
		changeState(ES_IDLE);
	}

};

bool Entity::willCollide(int cx, int cy) {
	return Game::me->willCollide(this, cx, cy);
}

std::string Entity::getStateName() {
	switch (state)
	{
	case ES_IDLE:
		return "IDLE";

	case ES_WALKING:
		return "WALKING";

	case ES_RUNNING:
		return "RUNNING";

	case ES_COVER:
		return "COVER";
	}
}
