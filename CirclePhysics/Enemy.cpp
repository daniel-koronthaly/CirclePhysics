#include "Enemy.h"
#include <iostream>

void Enemy::onDeath() {
	std::cout << "enemy died";
	_active = false;
}

void Enemy::onCollide() {

}

void Enemy::onCollideWall() {

}