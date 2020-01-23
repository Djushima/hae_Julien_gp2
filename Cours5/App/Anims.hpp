#pragma once

#include <SFML/Graphics.hpp>
#include <thread>

using namespace sf;

enum animName
{
	Shot,
	Explosion,
	Hit,
};

struct Frame {
	sf::IntRect rect;
	double duration; // in seconds
};

class Animation
{
private:
	animName Name;
	std::vector<Frame> frames;
	double totalLength = 0.0;
	double progress = 0.0;
	sf::Texture *spriteSheet = new Texture();
	

public:
	sf::Sprite *sprite = new Sprite();
	bool completed = false;


	Animation(animName index);

	~Animation();

	void update(double elapsed);

};
