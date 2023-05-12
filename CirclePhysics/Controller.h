#pragma once
#include "simplegui.h"
#include "Player.h"
#include <iostream>
using namespace simplegui;
class Controller : public KeyListener {
public:
	virtual void KeyDown(Window* win, int vk);
	const Vector2 getDirection() const;

private:
	Vector2 _direction;
};
