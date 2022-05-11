#include "InGame.h"

InGame::InGame() {
	SDL_Surface* bg_surface = IMG_Load("../../Resources/temp.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,900,420 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };
}

InGame::~InGame() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}

void InGame::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			printf("여기는 ingame의 keydown\n");
			if (event.key.keysym.sym == SDLK_SPACE) {
				g_current_game_phase = PHASE_ENDING;
			}
			break;
		}
	}
}

void InGame::Update() {

}

void InGame::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderPresent(g_renderer);
}