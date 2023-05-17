#pragma once
#include "Collider.h"
#include <string>
class Entity {
public:
	Entity(Collider c, std::string name, int health = 10, bool active = true);
	void setHealth(int h);
	int getHealth() const;
	int getMaxHealth() const;
	void subtractHealth(int h);
	void setActive(bool b);
	bool getActive() const;
	std::string getName() const;
	Collider* getCollider();
	const Collider* getCollider() const;
	virtual void onCollide() = 0;
	virtual void onCollideWall() = 0;
	virtual void onDeath() = 0;

protected:
	int _maxHealth;
	int _health;
	bool _active;
	Collider _collider;
	std::string _name;
};