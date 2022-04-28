#include "common.h"
#include "Intro.h"
#include "InGame.h"
#include "Ending.h"

SDL_Renderer* g_renderer;
bool g_flag_running;
phase game_phase=INTRO;

//À½¾Ç-¹è°æ
Mix_Music* Intro_music;
Mix_Music* Ending_music;
//À½¾Ç-È¿°úÀ½
Mix_Chunk* shooting_sound;
Mix_Chunk* riding_sound;
Mix_Chunk* treasure_sound;

SDL_Window* g_window;
Uint32 g_last_time_ms;
Uint32 g_frame_per_sec = 30;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING); // Initializing SDL library
	TTF_Init(); // Initializing TTF library

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("First Window", 100, 100, 640, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	g_last_time_ms = SDL_GetTicks();
	
	g_flag_running = true;
	Intro intro;
	InGame inGame;
	Ending ending;
	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
			continue;
		
		if (game_phase == INTRO) {
			intro.HandleEvents();
			intro.Render();
		}
		else if (game_phase == INGAME) {
			inGame.HandleEvents();
			inGame.Update();
			inGame.Render();
		}
		else if (game_phase == ENDING) {
			ending.HandleEvents();
			ending.Render();
		}
		g_last_time_ms = cur_time_ms;
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	//ClearGame();
	//Mix_FreeMusic(g_bg_mus);

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return 0;
}