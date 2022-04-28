#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class Person {
private:
	int x;
	int y;
	int missile_count;
	bool isRiding;
	bool haveTreasure;

	SDL_Texture* player_texture;
	SDL_Rect player_source;
	SDL_Rect player_destination;

public:
	Person(int x, int y, int missile_count = 0, bool isRiding = false, bool haveTreasure = false);
	void move(direction d);
	void show();
	int getX();
	int getY();
	bool getTreasure();
	bool getRidingState();
	void setRidingState(bool b);
	bool missileDecrease();
	void pickUpTreasure();
	void reset();
	void limit(int x, int y);
	int getMissileCount();
	~Person();
};

