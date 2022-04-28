#include "Ending.h"

Ending::Ending() {
	SDL_Surface* bg_surface = IMG_Load("../../Resources/Ending.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,640,600 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };

	Ending_music = Mix_LoadMUS("../../Resources/Ending.mp3");
	if (Ending_music == 0)
		std::cout << "Mix_LoadMUS(\"Ending.mp3\"): " << Mix_GetError() << std::endl;
}

void Ending::HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_RIGHT) {
				Mix_HaltMusic();
				game_phase = INTRO;
				Mix_PlayMusic(Intro_music, -1);
			}
			break;

		default:
			break;
		}
	}
}

void Ending::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderPresent(g_renderer);
}

Ending::~Ending() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}