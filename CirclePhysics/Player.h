#pragma once
#include "Entity.h"
#define NUM_LIVES 3
class Player : public Entity {
	using Entity::Entity;
	virtual void onDeath();
	virtual void onCollide();
	virtual void onCollideWall();
private:
	int _lives = NUM_LIVES;
};