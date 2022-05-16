#include "common.h"
#include "Intro.h"
#include "InGame.h"
#include "Ending.h"

//Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

//Game Phases
int g_current_game_phase;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("Game Window", 100, 100, 900, 500, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	
	//게임 시작
	g_flag_running = true;

	PhaseInterface* game_phases[3];
	game_phases[0] = new Intro;
	game_phases[1] = new InGame;
	game_phases[2] = new Ending;

	g_current_game_phase = PHASE_INTRO;

	while (g_flag_running) {
		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 100)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}

	for (int i = 0; i < 3; i++) {
		delete game_phases[i];
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}