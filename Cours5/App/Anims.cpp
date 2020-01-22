#include "Anims.hpp"

void Animation::Play(sf::RenderWindow &window) {
	while (completed == false) {
		window.draw(*sprite);
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
