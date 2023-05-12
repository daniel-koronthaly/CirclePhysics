#include "Player.h"
#include <iostream>

void Player::onDeath() {
	std::cout << "died";
	_active = false;
}

void Player::onCollide() {
	std::cout << "player collided\n";
	subtractHealth(1);
	std::cout << "player now has " + std::to_string(_health) + "health";
}

void Player::onCollideWall() {
	std::cout << "player collided with wall\n";
	subtractHealth(5);
	std::cout << "player now has " + std::to_string(_health) + "health";
}