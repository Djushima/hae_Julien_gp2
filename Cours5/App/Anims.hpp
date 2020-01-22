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
	sf::Texture *spriteSheet = nullptr;
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
	}

	~Animation() {
		if (spriteSheet) delete spriteSheet;
		spriteSheet = nullptr;
		if (sprite) delete sprite;
		sprite = nullptr;
	}

	void initAnim();

	void Play();;

};
