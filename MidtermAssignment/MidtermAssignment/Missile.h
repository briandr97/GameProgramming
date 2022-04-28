#pragma once
#include "common.h"

using namespace std;
extern SDL_Renderer* g_renderer;

class Missile {
private:
	bool state;
	direction d;

	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect missile_destination;

public:
	Missile(int x, int y, direction d, bool state = true);
	bool checkOut(int x1, int y1, int x2, int y2);
	void move(int n);
	void show();
	bool getState();
	int getX();
	int getY();
	~Missile();
};