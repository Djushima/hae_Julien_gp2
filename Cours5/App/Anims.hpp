#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

enum animName
{
	Shot,
	Explosion,
	Hit,
};

class Animation
{
private:
	animName Name;
	sf::Texture *spriteSheet = new Texture();
	sf::IntRect spriteRect;
	sf::Sprite *sprite = nullptr;
	sf::Clock clock;

	float spriteTime = 0.0f;
	float spriteSize = 0.0f;
	float spritesheetSize = 0.0f;
	bool completed = false;

public:
	Animation(animName index) {
		this->Name = index;
		switch (Name)
		{

		case Shot:
		{
			spriteTime = 0.3f;
			spritesheetSize = 384;
			spriteSize = 64;
			sf::IntRect newRect(0, 0, 64, 64);
			spriteRect = newRect;
			if (!spriteSheet->loadFromFile("Animations_SpriteSheet/Shot_Star.png"))
				printf("Load Shot Anim: Failed\n");
			sf::Sprite baseSprite(*spriteSheet, spriteRect);
			sprite = &baseSprite;
			break;
		}

		case Explosion:
		{
			spriteTime = 0.3f;
			spritesheetSize = 1000;
			spriteSize = 250;
			sf::IntRect newRect(0, 0, 250, 300);
			spriteRect = newRect;
			if (!spriteSheet->loadFromFile("Animations SpriteSheet/Explosion.png"))
				printf("Load Shot Anim: Failed\n");
			sf::Sprite baseSprite(*spriteSheet, spriteRect);
			sprite = &baseSprite;
			break;
		}

		case Hit:
		{
			spriteTime = 0.3f;
			spritesheetSize = 1000;
			spriteSize = 250;
			sf::IntRect newRect(0, 0, 250, 300);
			spriteRect = newRect;
			if (!spriteSheet->loadFromFile("Animations SpriteSheet/Big_Hit.png"))
				printf("Load Shot Anim: Failed\n");
			sf::Sprite baseSprite(*spriteSheet, spriteRect);
			sprite = &baseSprite;
			break;
		}

		default:
			printf("No anim Error");
			break;
		}
	}

	~Animation() {
		if (sprite) delete sprite;
		sprite = nullptr;
		if (spriteSheet) delete spriteSheet;
		spriteSheet = nullptr;
	}

	void Play(sf::RenderWindow &window);;

};
