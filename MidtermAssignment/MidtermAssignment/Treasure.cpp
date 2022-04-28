#include "Treasure.h"

Treasure::Treasure(int x, int y) {
	SDL_Surface* treasure_surface = IMG_Load("../../Resources/treasure.png");
	SDL_SetColorKey(treasure_surface, SDL_TRUE, SDL_MapRGB(treasure_surface->format, 255, 255, 255));
	treasure_texture = SDL_CreateTextureFromSurface(g_renderer, treasure_surface);
	SDL_FreeSurface(treasure_surface);
	treasure_source = { 0,0,400,280 };
	treasure_destination = { x, y, 100, 70 };
}

void Treasure::show() {
	SDL_RenderCopy(g_renderer, treasure_texture, &treasure_source, &treasure_destination);
}

bool Treasure::nearTreasure(int x, int y) {
	if ((x > treasure_destination.x - 50) && (x < treasure_destination.x + 50) &&
		(y > treasure_destination.y - 50) && (y < treasure_destination.y + 50))
		return true;
	else
		return false;
}

