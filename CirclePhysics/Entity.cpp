#include "Entity.h"


Entity::Entity(Collider c, std::string name, int health, bool active) : _collider(c), _name(name), _health(health), _active(active){}

void Entity::setHealth(int h) {
	_health = h;
}
void Entity::subtractHealth(int h) {
	_health -= h;
	if (_health <= 0) {
		onDeath();
	}
}
int Entity::getHealth() const {
	return _health;
}
void Entity::setActive(bool b) {
	_active = b;
}
bool Entity::getActive() const {
	return _active;
}

std::string Entity::getName() const {
	return _name;
}

Collider* Entity::getCollider() {
	return &_collider;
}

const Collider* Entity::getCollider() const {
	return &_collider;
}
