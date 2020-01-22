#include "Anims.hpp"

void Animation::initAnim() {
	switch (Name)
	{

	case Shot:
	{
		spriteTime = 0.3f;
		spritesheetSize = 1000;
		spriteSize = 250;
		sf::IntRect newRect(0, 0, 250, 300);
		spriteRect = newRect;
		if (!spriteSheet->loadFromFile("Animations SpriteSheet/Shot"))
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
		if (!spriteSheet->loadFromFile("Animations SpriteSheet/Explosion"))
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
		if (!spriteSheet->loadFromFile("Animations SpriteSheet/Hit"))
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

void Animation::Play() {
	while (completed = false) {
		if (clock.getElapsedTime().asSeconds() > spriteTime)
		{
			if (spriteRect.left == spritesheetSize)
				completed = true;
			else spriteRect.left += spriteSize;

			sprite->setTextureRect(spriteRect);
			clock.restart();
		}
	}
	delete this;
}
