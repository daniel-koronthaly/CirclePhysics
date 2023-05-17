#include "Model.h"
#include <iostream>

Model::Model(int width, int height) {
	_width = width;
	_height = height;
}

bool Model::resolveOutOfBoundsCollision(Collider& c) {
	bool val = false;
	if ((c.getPos().X - c.getWidth()/2) < 0 && c.getVelocity().X < 0) {
		Vector2 posNew;
		posNew.X = c.getWidth()/2;
		posNew.Y = c.getPos().Y;
		c.setPosition(posNew);

		Vector2 copy = c.getVelocity();
		copy.X *= -1;
		c.setVelocity(copy);
		val = true;
	}
	else if ((c.getPos().X + c.getWidth()/2) > _width && c.getVelocity().X > 0) {
		Vector2 posNew;
		posNew.X = _width - c.getWidth()/2;
		posNew.Y = c.getPos().Y;
		c.setPosition(posNew);

		Vector2 copy = c.getVelocity();
		copy.X *= -1;
		c.setVelocity(copy);
		val = true;
	}


	if ((c.getPos().Y - c.getHeight()/2) < 0 && c.getVelocity().Y < 0) {
		Vector2 posNew;
		posNew.Y = c.getHeight()/2;
		posNew.X = c.getPos().X;
		c.setPosition(posNew);

		Vector2 copy = c.getVelocity();
		copy.Y *= -1;
		c.setVelocity(copy);
		val = true;
	}
	else if ((c.getPos().Y + c.getHeight()/2) > _height && c.getVelocity().Y > 0) {
		Vector2 posNew;
		posNew.Y = _height - c.getHeight()/2;
		posNew.X = c.getPos().X;
		c.setPosition(posNew);

		Vector2 copy = c.getVelocity();
		copy.Y *= -1;
		c.setVelocity(copy);
		val = true;
	}
	return val;
};

void Model::update(double time, Vector2 dir) {
	for (int i = 0; i < _entities.size(); i++) {
		for (int j = i + 1; j < _entities.size(); j++) {
			if (checkCollision(*_entities.at(i)->getCollider(), *_entities.at(j)->getCollider())) {
				_entities.at(i)->onCollide();
				_entities.at(j)->onCollide();
				Collider& c1 = *_entities.at(i)->getCollider();
				Collider& c2 = *_entities.at(j)->getCollider();
				resolveCollision(c1, c2);
			}
		}
	}

	for (Entity* e : _entities) {
		Collider& c = *e->getCollider();
		physicsStep(c, time);
		if (resolveOutOfBoundsCollision(c)) {
			e->onCollideWall();
		}
	}
	playerControl(dir*PLAYER_SPEED);
}

void Model::playerControl(const Vector2 v) {
	_p->getCollider()->addVel(v);
}

void Model::resolveCollision(Collider& c1, Collider& c2)
{
	// get the mtd
	Vector2 delta = (c1.getPos() - c2.getPos());
	float d = getLength(delta);
	// minimum translation distance to push balls apart after intersecting
	Vector2 mtd = delta * (((c1.getHeight()/2 + c2.getHeight()/2) - d) / d);

	// resolve intersection --
	// inverse mass quantities
	float im1 = 1 / c1.getMass();
	float im2 = 1 / c2.getMass();

	// push-pull them apart based off their mass
	c1.addPos(mtd * (im1 / (im1 + im2)));
	c2.addPos((mtd * (im2 / (im1 + im2))) * -1);

	// impact speed
	Vector2 v = c1.getVelocity() - c2.getVelocity();
	float y = (c1.getVelocity().X * c2.getVelocity().Y) - (c2.getVelocity().X * c1.getVelocity().Y);
	float x = (c1.getVelocity().X * c2.getVelocity().X) + (c2.getVelocity().Y * c1.getVelocity().Y);
	float angle = atan2(y, x);
	float vn = angle * getLength(v) * getLength((mtd / getLength(mtd)));

	// sphere intersecting but moving away from each other already
	if (vn > 0.0f) {
		return;
	}
	// collision impulse
	float i = (-(1.0f + RESTITUTION) * vn) / (im1 + im2);
	Vector2 impulse = mtd / getLength(mtd) * i;

	// change in momentum
	c1.setVelocity(c1.getVelocity() + (impulse * im1));
	c2.setVelocity(c2.getVelocity() - (impulse * im2));

}

bool Model::checkCollision(Collider c1, Collider c2) {
	if (c1.getType() == 0 && c2.getType() == 0) {
		return checkCircleCollision(c1.getPos(), c1.getHeight()/2, c2.getPos(), c2.getHeight()/2);
	}
	else {
		//Non circular colliders
		return false;
	}
}

bool Model::checkCircleCollision(Vector2 c1pos, float c1rad, Vector2 c2pos, float c2rad) {
	return ((c1pos.X - c2pos.X) * (c1pos.X - c2pos.X) + (c1pos.Y - c2pos.Y) * (c1pos.Y - c2pos.Y)) < (c1rad + c2rad) * (c1rad + c2rad);
}

void Model::physicsStep(Collider& c, double time){
	if (FRICTION_ENABLED) {
		Vector2 F = c.getVelocity() * -FRICTION_COEFFICIENT;
		Vector2 a = F / c.getMass();
		c.addVel(a * time);
	}
	c.addPos(c.getVelocity() * time);
}

void Model::addEntity(Entity* c) {
	_entities.push_back(c);
}

int Model::getHeight() {
	return _height;
}

int Model::getWidth() {
	return _width;
}

const Player* Model::getPlayer() const {
	return _p;
}

void Model::setPlayer(Player* p) {
	_p = p;
}

std::vector<Entity*> Model::getEntities() {
	return _entities;
}