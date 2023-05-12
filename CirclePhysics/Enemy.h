#pragma once
#include "Entity.h"
class Enemy : public Entity {
	using Entity::Entity;
	virtual void onDeath();
	virtual void onCollide();
	virtual void onCollideWall();
};