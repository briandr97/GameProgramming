#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;
extern Mix_Music* Ending_music;
extern Mix_Music* Intro_music;

class Ending {
private:
	//그림-배경
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;

	

public:
	Ending();
	void HandleEvents();
	void Render();
	~Ending();
};