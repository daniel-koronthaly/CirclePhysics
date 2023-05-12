#include "Collider.h"

Collider::Collider(Vector2 position, Vector2 velocity, float width, float height, float mass, simplegui::Color color, int type) :
	_position(position), _velocity(velocity), _width(width), _height(height), _mass(mass), _color(color), _type(type) {}

const Vector2& Collider::getPos() const {
	return _position;
}
const Vector2& Collider::getVelocity() const {
	return _velocity;
}
float Collider::getWidth() const {
	return _width;
}
float Collider::getHeight() const {
	return _height;
}
float Collider::getMass() const {
	return _mass;
}
simplegui::Color Collider::getColor() const {
	return _color;
}
int Collider::getType() const {
	return _type;
}
void Collider::addPos(const Vector2& toAdd) {
	_position = _position + toAdd;
}
void Collider::addVel(const Vector2& toAdd) {
	_velocity = _velocity + toAdd;
}
void Collider::setVelocity(const Vector2& vel) {
	_velocity.X = vel.X;
	_velocity.Y = vel.Y;
	float length = getLength(_velocity);
	if (length >= 200) {
		_velocity *= (200 / length);
	}
}
void Collider::setPosition(const Vector2& pos) {
	_position.X = pos.X;
	_position.Y = pos.Y;
}


