#include "Game.hpp"
#include "Entity.hpp"

Game* Game::me = nullptr;
static bool wasPressed[sf::Keyboard::KeyCount];
int CoverCount = 0;

void Game::init() {
	RectangleShape *sh = new RectangleShape(Vector2f(12, 24));
	sh->setFillColor(sf::Color::Magenta);
	sh->setOrigin(6, 24);

	Entity * ent = new Entity(sh);
	ent->setPosePixel(100, 600);
	evec.push_back(ent);
	player = ent;
	me = this;

	for (int i = 0; i < (1280 / Entity::CELL_WIDTH); i++)
	{
		if (i == 0 || i == (1280 / Entity::CELL_WIDTH)-1)
			for (int j = 0; j < (720 / Entity::CELL_WIDTH)-1; j++)
			{
				platforms.push_back(Vector2i(i, j));
			}

		for (int j = 0; j < (720 / Entity::CELL_WIDTH); j++)
		{
			if (j == 0 || j == (720 / Entity::CELL_WIDTH)-1)
			{
				platforms.push_back(Vector2i(i, j));
			}
		}
	}
}

void Game::update(double dt)
{
	for (auto it = evec.begin(); it != evec.end();) {
		Entity * ent = *it;
		ent->update(dt);
		it++;
	}
}

void Game::draw(RenderWindow & win)
{
	for (auto it = evec.begin(); it != evec.end();) {
		Entity * ent = *it;
		ent->draw(win);
		it++;
	}

	auto CW = Entity::CELL_WIDTH;
	RectangleShape cell;
	cell.setFillColor(sf::Color(0x918EF0ff));
	cell.setSize(Vector2f(CW, CW));
	for (Vector2i & pl : platforms) {
		cell.setPosition(pl.x * CW, pl.y * CW);
		win.draw(cell);
	}

	for (auto it = pvec.begin(); it != pvec.end();) {
		Particle * p = *it;
		p->update();
		if (p->killed) {
			it = pvec.erase(it);
		}
		else {
			p->draw(win);
			it++;
		}
	}
}

bool Game::willCollide(int cx, int cy)
{
	int cScreenWidth = 1280 / Entity::CELL_WIDTH;
	int cScreenHeight = 720 / Entity::CELL_WIDTH;

	if (cx < 1) return true;
	else if (cx >= cScreenWidth) return true;

	if (cy < 1) return true;
	else if (cy >= cScreenHeight) return true;

	for (Vector2i & cell : platforms)
	{
		if (cell.x == cx && cell.y == cy)
			return true;
		if (cell.x == cx && cell.y == cy - 1)
			return true;
	}

	return false;
}

void Game::togglePlatform(int cx, int cy)
{
	for (auto it = platforms.begin(); it != platforms.end(); it++) {
		Vector2i & pl = *it;
		if (pl.x == cx && pl.y == cy) {
			platforms.erase(it);
			return;
		}
	}
	platforms.push_back(Vector2i(cx, cy));


}