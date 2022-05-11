#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;

class Ending : public PhaseInterface {
public:
	Ending();
	~Ending();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;

	SDL_Texture* restart_texture;
	SDL_Rect restart_source;
	SDL_Rect restart_destination;
};