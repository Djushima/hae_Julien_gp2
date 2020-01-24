#include "Anims.hpp"

Animation::Animation(animName index, Entity *obj, float angle) {
	this->Name = index;
	this->Parent = obj;
	this->angle = angle;
	switch (Name)
	{

	case Shot:
	{
		if (!spriteSheet->loadFromFile("Animations_SpriteSheet/Shot_Star.png"))
			printf("Error load Shot anim");
		sprite->setOrigin(Vector2f(32, 32));
		sprite->setPosition(Vector2f(Parent->sprite->getPosition().x + cos(angle) * 32, Parent->sprite->getPosition().y + sin(angle) * 32));
		sprite->setRotation(angle * (180 / 3.14) + 90);
		sprite->setTexture(*spriteSheet);
		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		frames.push_back({ sf::IntRect(0,0,64,64), 0.1 });
		frames.push_back({ sf::IntRect(64,0,64,64), 0.1 });
		frames.push_back({ sf::IntRect(128,0,64,64), 0.1 });
		frames.push_back({ sf::IntRect(192,0,64,64), 0.1 });
		frames.push_back({ sf::IntRect(256,0,64,64), 0.1 });
		frames.push_back({ sf::IntRect(320,0,64,64), 0.1 });
		totalLength = 0.6;
		break;
	}

	case Explosion:
	{
		if (!spriteSheet->loadFromFile("Animations_SpriteSheet/Shot_Star.png"))
			printf("Error load Shot anim");
		sprite->setTexture(*spriteSheet);
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		totalLength = 0.3;
		break;
	}

	case Hit:
	{
		if (!spriteSheet->loadFromFile("Animations_SpriteSheet/Shot_Star.png"))
			printf("Error load Shot anim");
		sprite->setTexture(*spriteSheet);
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		frames.push_back({ sf::IntRect(0,0,0,0), 0.05 });
		totalLength = 0.3;
		break;
	}

	default:
		printf("No anim Error");
		break;
	}
}

Animation::~Animation() {
	if (spriteSheet) delete spriteSheet;
	spriteSheet = nullptr;
	if (sprite) delete sprite;
	sprite = nullptr;
	if (Parent) delete Parent;
	Parent = nullptr;
}

void Animation::update(double elapsed) {
	progress += elapsed;
	double p = progress;
	for (int i = 0; i < frames.size(); i++) {
		p -= frames[i].duration;
		if (p <= 0.0 || &(frames[i]) == &frames.back())
		{
			sprite->setTextureRect(frames[i].rect);
			break;
		}
		if (progress >= totalLength)
			completed = true;
	}
}
