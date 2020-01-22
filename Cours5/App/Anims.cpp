#include "Anims.hpp"

void Animation::Play(sf::RenderWindow &window) {
	while (completed == false) {
		sprite->setPosition(640, 360);
		window.draw(*sprite);
		window.display();
		if (clock.getElapsedTime().asSeconds() > spriteTime)
		{
			if (spriteRect.left == spritesheetSize)
				completed = true;
			else spriteRect.left += spriteSize;

			sprite->setTextureRect(spriteRect);
			clock.restart();
		}
		window.clear();
	}
	delete this;
}
