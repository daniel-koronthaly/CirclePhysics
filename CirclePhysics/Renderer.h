#pragma once
#include "simplegui.h"
#include "Vector2.h"
#include <vector>
#include "Model.h"
using namespace simplegui;

class Renderer : public Painter {
public:
	Renderer(Model* m);
	virtual void Paint(Window* win, Graphics* g);
	void PaintArrow(Window* win, Graphics* g, Vector2 pos, Vector2 vel, float height);
	void PaintHUD(Window* win, Graphics* g);
	const bool getDrawing() const;
	void setDrawing(bool b);
	const std::string getDefault() const;
	void setDefault(std::string s);
	void setCurrTime(double d);
private:
	Model* _m;
	double _currTime = 0;
	bool _drawing = true;
	std::string _defaultDisplay = "You are dead.";
};