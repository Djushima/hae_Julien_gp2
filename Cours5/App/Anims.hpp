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
	sf::Texture *SpriteSheet = nullptr;
	sf::IntRect spriteRect;
	sf::Sprite *sprite = nullptr;
	sf::Clock clock;

	float spriteTime = 0.0f;
	float spriteSize = 0.0f;
	float spritesheetSize = 0.0f;

public:
	bool completed = false;

	Animation(animName index) {
		this->Name = index;
	}

	~Animation() {
		
	}

	void initAnim() {
		switch (Name)
		{

		case Shot:
			break;

		case Explosion:
			break;

		case Hit:
			break;

		default:
			break;
		}
	}

	void Play() {
		while (completed = false) {
			if (clock.getElapsedTime().asSeconds() > 0.5f)
			{
				if (spriteRect.left == spritesheetSize)
					completed = true;
				else spriteRect.left += spriteSize; /*SpriteSize*/

				sprite->setTextureRect(spriteRect);
				clock.restart();
			}
		}
	};

};
