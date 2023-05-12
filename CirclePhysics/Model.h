#pragma once
#include "Entity.h"
#include <vector>
#include "Player.h"
#define RESTITUTION 1.0f
#define FRICTION_ENABLED true
#define FRICTION_COEFFICIENT 0.8f
#define PLAYER_SPEED 2
class Model {
public:
	Model(int width, int height);
	bool resolveOutOfBoundsCollision(Collider& c);
	void update(double time, Vector2 dir);
	void resolveCollision(Collider& c1, Collider& c2);
	bool checkCollision(Collider c1, Collider c2);
	bool checkCircleCollision(Vector2 c1pos, float c1rad, Vector2 c2pos, float c2rad);
	void physicsStep(Collider& c, double time);
	void playerControl(const Vector2 v);
	void addEntity(Entity* c);
	int getHeight();
	int getWidth();
	void setPlayer(Player* p);
	std::vector<Entity*> getEntities();
private:
	int _width;
	int _height;
	std::vector<Entity*> _entities;
	Player* _p;
};