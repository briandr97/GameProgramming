#include "Tank.h"

Tank::Tank(int x, int y) {
	this->x = x;
	this->y = y;
	this->w = 77;
	this->h = 80;

	SDL_Surface* tank_surface = IMG_Load("../../Resources/tank_sheet.jpg");
	SDL_SetColorKey(tank_surface, SDL_TRUE, SDL_MapRGB(tank_surface->format, 255, 255, 255));
	tank_texture = SDL_CreateTextureFromSurface(g_renderer, tank_surface);
	SDL_FreeSurface(tank_surface);

	for (int i = 0; i < 4; i++)
		tank_source.emplace_back();
	tank_source[LEFT] = { 0,0,w,h };
	tank_source[RIGHT] = { 0, 102, w, h };
	tank_source[UP] = { 115,0,w,h };
	tank_source[DOWN] = { 115,109,w,h };
	tank_destination = { x - w / 2, y - h / 2, w, h };
}

void Tank::show(direction d) {
	SDL_RenderCopy(g_renderer, tank_texture, &tank_source[d], &tank_destination);
}

bool Tank::nearTank(int x, int y) {
	if ((x > this->x - 60) && (x < this->x + 20) &&
		(y > this->y - 60) && (y < this->y + 20))
		return true;
	else
		return false;
}

int Tank::getX() {
	return this->x;
}

int Tank::getY() {
	return this->y;
}

int Tank::getW() {
	return this->w;
}

int Tank::getH() {
	return this->h;
}

Tank::~Tank() {
	SDL_DestroyTexture(tank_texture);
}