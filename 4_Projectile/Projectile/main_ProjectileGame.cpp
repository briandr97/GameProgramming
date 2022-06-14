#include <iostream>
#include "ProjectileGame.h"


/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;

// 초단위 timestep (1/60초). Frame time과 시뮬레이션의 timestep으로 사용된다.
float g_timestep_s = 1.0f / 60.0f;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	g_window = SDL_CreateWindow("Projectile", 100, 100, 1000, 700, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	ProjectileGame game;	

	g_last_time_ms = SDL_GetTicks();

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < (1000 * g_timestep_s)) // 밀리세턴드 단위로 변환하기 위해 1000 곱함
			continue;
		
		game.HandleEvents();
		game.Update();
		game.Render();

		g_last_time_ms = cur_time_ms;
	}

	
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	SDL_Quit();

	return 0;

	return 0;
}

