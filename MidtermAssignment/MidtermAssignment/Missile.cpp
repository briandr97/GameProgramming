#include "Missile.h"

Missile::Missile(int x, int y, direction d, bool state) {
	this->d = d;
	this->state = state;

	SDL_Surface* bullet_surface = IMG_Load("../../Resources/missile3.png");
	//SDL_SetColorKey(bullet_surface, SDL_TRUE, SDL_MapRGB(bullet_surface->format, 255, 255, 255));
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, bullet_surface);
	SDL_FreeSurface(bullet_surface);
	missile_source = { 0,0,900,278 };
	missile_destination = { x, y, missile_source.w/90, missile_source.h/90 };
}

void Missile::move(int n) {
	switch (d) {
	case LEFT:
		missile_destination.x -= n;
		printf("미사일 왼쪽으로 가라!\n");
		break;
	case RIGHT:
		missile_destination.x += n;
		break;
	case UP:
		missile_destination.y -= n;
		break;
	case DOWN:
		missile_destination.y += n;
		break;
	default:
		break;
	}
}

bool Missile::checkOut(int x1, int y1, int x2, int y2) {
	if ((missile_destination.x < (x1 - 100)) ||
		(missile_destination.x > (x2 + 100)) ||
		(missile_destination.y > (y1 - 100)) ||
		(missile_destination.y < (y1 + 100))) {
		this->state = false;
	}
	return this->state;
}

void Missile::show() {
	printf("진짜 show 됐다고?\n");
	SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
	printf("미사일 좌표: %d, %d\n", missile_destination.x, missile_destination.y);
}

bool Missile::getState() {
	return this->state;
}

int Missile::getX() {
	return missile_destination.x;
}

int Missile::getY() {
	return missile_destination.y;
}

Missile::~Missile() {
	SDL_DestroyTexture(missile_texture);
}