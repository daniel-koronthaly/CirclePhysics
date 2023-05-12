#include "Controller.h"

class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

void Controller::KeyDown(Window* win, int vk) {
	if (vk == simplegui::KEY_W) {
		std::cout << "w key";
		_direction.X = 0;
		_direction.Y = -1;
	}
	else if (vk == simplegui::KEY_A) {
		std::cout << "a key";
		_direction.X = -1;
		_direction.Y = 0;
	}
	else if (vk == simplegui::KEY_S) {
		std::cout << "s key";
		_direction.X = 0;
		_direction.Y = 1;
	}
	else if (vk == simplegui::KEY_D) {
		std::cout << "d key";
		_direction.X = 1;
		_direction.Y = 0;
	}
	else if (vk == simplegui::KEY_I) {
		std::cout << "i key";
	}
};

const Vector2 Controller::getDirection() const {
	return _direction;
}

