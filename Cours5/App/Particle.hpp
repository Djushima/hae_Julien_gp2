#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

enum prtType {
	Eplode,
	Trail,
};

class Particle
{
private:
	
	Vector2f Speed;
	float Life, baseLife;
	sf::Color clr;
	sf::Shape *Shp;
	sf::Texture *smoke = nullptr;
	prtType Type;

public:
	bool Killed = false;

	Particle(sf::Shape *shape, Vector2f speed, float life, sf::Color color, sf::Texture *tex, prtType type) {
		this->Shp = shape;
		this->Speed = speed;
		this->Life = life;
		this->baseLife = life;
		this->clr = color;
		smoke = tex;
		Shp->setTexture(smoke);
		this->Type = type;
	};


	~Particle() {
		if (Shp) delete Shp;
		Shp = nullptr;
		if (smoke) delete smoke;
		smoke = nullptr;
	};

	void Update()
	{
		switch (Type)
		{
		case Eplode:
			if (Life > 0)
			{
				Shp->setPosition(Vector2f(Shp->getPosition().x + Speed.x, Shp->getPosition().y + Speed.y));
				if (Shp->getFillColor().a != 0)
					Shp->setFillColor(sf::Color(clr.r, Shp->getFillColor().g, clr.b, Shp->getFillColor().a - (255 / baseLife)));
				if (Shp->getFillColor().g != 175)
					Shp->setFillColor(sf::Color(clr.r, Shp->getFillColor().g + (510/baseLife), clr.b, Shp->getFillColor().a));
				Life--;
			}
			else Killed = true;
			break;

		case Trail:
			break;
		}
		
	}

	void draw(RenderWindow &win)
	{
		win.draw(*Shp);
	}

};