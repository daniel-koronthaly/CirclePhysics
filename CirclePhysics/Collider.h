#pragma once
#include "Vector2.h"
#include "simplegui.h"


enum shape {
	TYPE_CIRCLE = 0,
	TYPE_BOX = 1
};
class Collider {
public:
	Collider(Vector2 position, Vector2 velocity, float height, float width, float mass, simplegui::Color color = simplegui::Color(0xff, 0xff, 0xff), int type = 0);
	const Vector2& getPos() const;
	const Vector2& getVelocity() const;
	float getWidth() const;
	float getHeight() const;
	float getMass() const;
	simplegui::Color getColor() const;
	int getType() const;
	void addPos(const Vector2& toAdd);
	void addVel(const Vector2& toAdd);
	void setVelocity(const Vector2& vel);
	void setPosition(const Vector2& vel);
private:
	Vector2 _position;
	Vector2 _velocity;
	float _height;
	float _width;
	float _mass;
	simplegui::Color _color;
	int _type;
};