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
	const bool getDrawing() const;
	void setDrawing(bool b);
	const std::string getDefault() const;
	void setDefault(std::string s);
private:
	Model* _m;
	bool _drawing = true;
	std::string _defaultDisplay = "You are dead.";
};