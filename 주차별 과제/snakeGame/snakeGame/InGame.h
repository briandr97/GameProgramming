#pragma once
#include "common.h"
#include <list>
#include <stdlib.h>
#include <time.h>

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

class InGame : public PhaseInterface {
public:
	InGame();
	~InGame();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;

	void Reset();

private:
	//bg
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;
	
	//snake
	SDL_Texture* snake_texture;
	SDL_Rect snake_source;
	SDL_Rect snake_destination;
	
	//item
	SDL_Texture* item_texture;
	SDL_Rect item_source;
	SDL_Rect item_destination;
	boolean item_exist;
	
	//font
	TTF_Font* font;
	SDL_Color blue;
	SDL_Texture* game_over_texture;
	SDL_Rect game_over_text;
	SDL_Rect game_over_destination;

	enum d {LEFT, RIGHT, UP, DOWN, STOP};
	int direction;
	int randomX, randomY;
	list<SDL_Rect> snake;
	const int WIDTH = 10;
	const int HEIGHT = 10;
	boolean game_over;
	boolean game_over_click;
};