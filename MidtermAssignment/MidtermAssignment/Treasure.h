#pragma once
#include "common.h"
extern SDL_Renderer* g_renderer;

class Treasure {
private:
	SDL_Texture* treasure_texture;
	SDL_Rect treasure_source;
	SDL_Rect treasure_destination;

public:
	Treasure(int x, int y);
	int getX();
	int getY();
	int getW();
	int getH();
	void show();
	bool nearTreasure(int x, int y);
	~Treasure();
};