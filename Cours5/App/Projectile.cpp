#include "Projectile.hpp"

void Projectile::Move() {
	x += dir.x * speed;
	y += dir.y * speed;
	this->sprite->setPosition(x, y);
	this->box = this->sprite->getGlobalBounds();
	Entity::Move();
}

void Projectile::Rebond(Entity * Object2) {
	auto Obj1Pos = this->sprite->getPosition();
	auto Obj2Pos = Object2->sprite->getPosition();
	auto Obj2Ofs = Object2->box;

	if ((Obj1Pos.x > Obj2Pos.x + Obj2Ofs.width) || (Obj1Pos.x < Obj2Pos.x))
		this->dir = Vector2f(-this->dir.x, this->dir.y);
	else if ((Obj1Pos.y > Obj2Pos.y + Obj2Ofs.height) || (Obj1Pos.y < Obj2Pos.y))
		this->dir = Vector2f(this->dir.x, -this->dir.y);
	this->sprite->setRotation(PI - this->sprite->getRotation());
	this->Bounced = true;
}
