#include "chrono"
#include "vector"
#include "Vector2.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Collider.h"
#include <windows.h>
#include "Model.h"
#include "Renderer.h"
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"

#define WINDOW_HEIGHT 750
#define WINDOW_WIDTH 750
#define MS_PER_FRAME 10
#define COLLIDER_MASS_DEFAULT 1
#define COLLIDER_WIDTH_DEFAULT 5
#define COLLIDER_HEIGHT_DEFAULT 5

#define RAND_COLLIDERS_INITIALIZED 15
#define INIT_FROM_FILE false
#define MAX_WIDTH_HEIGHT 40
#define MIN_WIDTH_HEIGHT 8
#define MAX_AXIS_VELOCITY 60
#define MASS_WIDTH_HEIGHT_RATIO 10
#define MAX_RGB 255

#define HEIGHT 500
#define WIDTH 500





std::vector<std::string> split(std::string str) {
	std::vector<std::string> strings;
	int startIndex = 0, endIndex = 0;
	for (int i = 0; i <= str.size(); i++) {

		// If we reached the end of the word or the end of the input.
		if (str[i] == ',' || i == str.size()) {
			endIndex = i;
			std::string temp;
			temp.append(str, startIndex, endIndex - startIndex);
			strings.push_back(temp);
			startIndex = endIndex + 1;
		}
	}
	return strings;
}

Collider createColliderFromLine(std::vector<std::string> values) {
	Vector2 pos;
	pos.X = stof(values.at(0));
	pos.Y = stof(values.at(1));
	Vector2 vel;
	vel.X = stof(values.at(2));
	vel.Y = stof(values.at(3));
	float width_height = stof(values.at(4));
	float mass = stof(values.at(5));
	int type = stoi(values.at(6));
	return Collider(pos, vel, width_height, width_height, mass, Color(0xff, 0xff, 0xff), type);
}

void instantiateCollidersFromFile(Model& m) {
	std::fstream in_file{ "./colliders.txt", std::ios::in };
	std::string line;
	int lineNum = 0;
	if (in_file.is_open()) {
		while (!in_file.eof()) {
			getline(in_file, line);
			if (line.size() == 0) {
				continue;
			}
			std::vector<std::string> values = split(line);
			Collider c = createColliderFromLine(values);
			std::string name = "enemy" + std::to_string(lineNum);
			Enemy* e = new Enemy(c, name);
			m.addEntity(e);
			lineNum++;
		}

	}
	else {
		throw "Colliders failed.";
	}
}

int main() {

	Model m = Model(WIDTH, HEIGHT);


	if (INIT_FROM_FILE) {
		try {
			instantiateCollidersFromFile(m);
		}
		catch (...) {
			std::cout << "Instantiating Colliders has failed\n";
			return EXIT_FAILURE;
		}
	}
	else {
		for (int i = 0; i < RAND_COLLIDERS_INITIALIZED; i++) {
			Vector2 pos;
			float width_height = rand() % (MAX_WIDTH_HEIGHT - MIN_WIDTH_HEIGHT) + MIN_WIDTH_HEIGHT;
			float mass = width_height * MASS_WIDTH_HEIGHT_RATIO;
			int color = MAX_RGB - ((mass - (MAX_WIDTH_HEIGHT * MASS_WIDTH_HEIGHT_RATIO)) / ((MAX_WIDTH_HEIGHT - MIN_WIDTH_HEIGHT) * MASS_WIDTH_HEIGHT_RATIO) * MAX_RGB);
			pos.X = fmod(rand(), (m.getWidth() - width_height)) + width_height/2;
			pos.Y = fmod(rand(), (m.getHeight() - width_height)) + width_height/2;
			Vector2 vel;
			vel.X = rand() % (MAX_AXIS_VELOCITY);
			vel.Y = rand() % (MAX_AXIS_VELOCITY);
			Collider c = Collider(pos, vel, width_height, width_height, mass, Color(color, color, color), 0);
			std::string name = "enemy" + std::to_string(i);
			Enemy* e = new Enemy(c, name);
			m.addEntity(e);
		}
	}

	Vector2 startPos;
	startPos.X = m.getWidth()/2;
	startPos.Y = m.getHeight()/2;
	Vector2 startVel = Vector2();
	Color c = Color(c.MAGENTA);
	Collider hitbox = Collider(startPos, startVel, MIN_WIDTH_HEIGHT, MIN_WIDTH_HEIGHT, 1, c, 0);
	Player* p =  new Player(hitbox, "Player");
	m.addEntity(p);
	m.setPlayer(p);


	Renderer r = Renderer(&m);
	Controller controller = Controller();
	Window* window = Window::Create(WINDOW_WIDTH, WINDOW_HEIGHT, "Circles");
	window->SetPainter(&r);
	window->SetKeyListener(&controller);
	window->Show(true);

	

	auto start = std::chrono::system_clock::now();
	auto previous = std::chrono::system_clock::now();
	while (p->getActive() && !window->IsDisposed()) {
		for (int i = 0; i < m.getEntities().size(); i++) {
			/*Entity* e = m.getEntities().at(i);*/
			/*std::string debug = "Player is at " + std::to_string(p->getCollider()->getPos().X) + "," + std::to_string(p->getCollider()->getPos().Y) + "\n\n";
			std::cout << debug;*/
		}
		auto current = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = current - previous;
		previous = current;
		Vector2 v = controller.getDirection();
		m.update(elapsed_seconds.count(), v);
		std::chrono::duration<double> timer = current - start;
		r.setCurrTime(timer.count());
		window->Invalidate();
		if (elapsed_seconds.count() * 1000 < MS_PER_FRAME) {
			Sleep(MS_PER_FRAME - (elapsed_seconds.count() * 1000));
		}
	}
	if (!p->getActive()) {
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> time_alive = end - start;
		std::string s = "You are dead. You survived " + std::to_string(time_alive.count()) + " seconds.";
		r.setDefault(s);
		r.setDrawing(false);
		window->Invalidate();
		std::cout << s;
		Sleep(5000);
	}

	
	window->Dispose();
	delete window;
	for (int i = 0; i < m.getEntities().size(); i++) {
		Entity* e = m.getEntities().at(i);
		delete e;
	}
	return 0;

}
