#include "Renderer.h"
#include <iostream>

#define ARROW_HEAD_LENGTH 20
#define ARROW_HEAD_MIN_LENGTH 5.0f
#define ARROW_DEGREES 25
#define ARROW_DRAW_MIN_VEL 5
#define ARROW_VEL_SCALE 0.0035
#define ARROW_DRAW false

#define HUD_VERT_OFFSET 30
#define HUD_HOR_OFFSET 10

#define HEALTHBAR_LENGTH 300

constexpr float PI = 3.1415;
constexpr float RAD_CONVERSION = PI / 180;

Renderer::Renderer(Model* m) {
	_m = m;
}

void Renderer::Paint(Window* win, Graphics* g) {
	if (_drawing) {
		g->Clear();
		
		g->FillRect(0, 0, _m->getWidth(), _m->getHeight());

		for (Entity* e : _m->getEntities()) {
			const Collider& c = *e->getCollider();
			Color color = c.getColor();
			g->SetFillColor(color);

			float height = c.getHeight();
			float width = c.getWidth();
			Vector2 pos = c.getPos();
			Vector2 vel = c.getVelocity();
			g->DrawEllipse(pos.X - width / 2, pos.Y - height / 2, width, height);
			if (ARROW_DRAW) {
				PaintArrow(win, g, pos, vel, height);
			}

			PaintHUD(win, g);
			
			g->SetFillColor(255, 255, 255);
		}
	}
	else {
		g->Clear();
		g->SetColor(Color::DARK_RED);
		g->DrawString(20, 20, _defaultDisplay.c_str());
	}
};

void Renderer::PaintArrow(Window* win, Graphics* g, Vector2 pos, Vector2 vel, float height) {
	if (!(abs(vel.X) < ARROW_DRAW_MIN_VEL && abs(vel.Y) < ARROW_DRAW_MIN_VEL)) {
		float scalingFactor = getLength(vel) * ARROW_VEL_SCALE;
		Vector2 offset = pos + vel / getLength(vel) * height / 2;
		Vector2 endpoint = offset;
		endpoint.X += vel.X * scalingFactor;
		endpoint.Y += vel.Y * scalingFactor;
		g->DrawLine(offset.X, offset.Y, endpoint.X, endpoint.Y);

		float angle = atan2(endpoint.Y - offset.Y, endpoint.X - offset.X) + PI;

		float arrowSize = std::max(ARROW_HEAD_LENGTH * scalingFactor, ARROW_HEAD_MIN_LENGTH);

		float x1 = endpoint.X + arrowSize * cos(angle - ARROW_DEGREES * RAD_CONVERSION);
		float y1 = endpoint.Y + arrowSize * sin(angle - ARROW_DEGREES * RAD_CONVERSION);
		float x2 = endpoint.X + arrowSize * cos(angle + ARROW_DEGREES * RAD_CONVERSION);
		float y2 = endpoint.Y + arrowSize * sin(angle + ARROW_DEGREES * RAD_CONVERSION);

		g->DrawLine(endpoint.X, endpoint.Y, x1, y1);
		g->DrawLine(endpoint.X, endpoint.Y, x2, y2);

	}
}

void Renderer::PaintHUD(Window* win, Graphics* g) {
	int modelHeight = _m->getHeight();
	int modelWidth = _m->getWidth();

	int currHealth = _m->getPlayer()->getHealth();
	int maxHealth = _m->getPlayer()->getMaxHealth();

	g->SetFillColor(Color::WHITE);
	g->FillRect(HUD_HOR_OFFSET, modelHeight + HUD_VERT_OFFSET, 300, 30);
	g->SetFillColor(Color::DARK_RED);
	g->FillRect(HUD_HOR_OFFSET, modelHeight + HUD_VERT_OFFSET, 300.0 * (float)currHealth / maxHealth, 30);

	std::string str = std::to_string(_currTime);
	int ind = str.find('.');
	str = str.substr(0, ind + 3);

	g->DrawString(modelWidth - HUD_HOR_OFFSET - 30, modelHeight + HUD_VERT_OFFSET, str.c_str());

}

const bool Renderer::getDrawing() const {
	return _drawing;
}	

void Renderer::setDrawing(bool b) {
	_drawing = b;
}

const std::string Renderer::getDefault() const {
	return _defaultDisplay;
}

void Renderer::setDefault(std::string s) {
	_defaultDisplay = s;
}

void Renderer::setCurrTime(double d) {
	_currTime = d;
}