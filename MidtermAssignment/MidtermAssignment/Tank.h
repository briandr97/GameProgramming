#pragma once
#include "common.h"

using namespace std;
extern SDL_Renderer* g_renderer;

class Tank {
private:
	int x, y, w, h;
	SDL_Texture* tank_texture;
	vector<SDL_Rect> tank_source;
	SDL_Rect tank_destination;

public:
	Tank(int x, int y);
	int getX();
	int getY();
	int getW();
	int getH();
	void show(direction d);
	bool nearTank(int x, int y);
	~Tank();
};