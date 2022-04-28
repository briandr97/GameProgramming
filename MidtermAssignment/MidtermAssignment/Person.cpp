#include "Person.h"

Person::Person(int x, int y, int missile_count, bool isRiding, bool haveTreasure) {
	this->x = x;
	this->y = y;
	this->missile_count;
	this->isRiding = isRiding;
	this->haveTreasure = haveTreasure;

	SDL_Surface* player_surface = IMG_Load("../../Resources/player.jpg");
	SDL_SetColorKey(player_surface, SDL_TRUE, SDL_MapRGB(player_surface->format, 255, 255, 255));
	player_texture = SDL_CreateTextureFromSurface(g_renderer, player_surface);
	SDL_FreeSurface(player_surface);
	player_source = { 0,0,131,191 };
	int temp_w = player_source.w * 0.33;
	int temp_h = player_source.h * 0.33;
	player_destination = { x-temp_w/2, y-temp_h/2, temp_w, temp_h };
}

void Person::move(direction d) {
	switch (d) {
	case LEFT:
		player_destination.x -= 10;
		break;
	case RIGHT:
		player_destination.x += 10;
		break;
	case UP:
		player_destination.y -= 10;
		break;
	case DOWN:
		player_destination.y += 10;
		break;
	}
}

void Person::limit(int x, int y) {
	if (player_destination.x < 0) {
		player_destination.x = 0;
	}
	else if (player_destination.x > x-player_destination.w) {
		player_destination.x = x - player_destination.w;
	}
	else if (player_destination.y < 0) {
		player_destination.y = 0;
	}
	else if (player_destination.y > y - player_destination.h) {
		player_destination.y = y - player_destination.h;
	}
}

void Person::show() {
	if (!isRiding) {
		SDL_RenderCopy(g_renderer, player_texture, &player_source, &player_destination);
	}
}

bool Person::getRidingState() {
	return this->isRiding;
}
void Person::setRidingState(bool b) {
	this->isRiding = b;
}

int Person::getMissileCount() {
	return missile_count;
}

int Person::getX() {
	return player_destination.x;
}

int Person::getY() {
	return player_destination.y;
}

void Person::pickUpTreasure() {
	this->haveTreasure = true;
	this->missile_count += 5;
}

bool Person::getTreasure() {
	return this->haveTreasure;
}

bool Person::missileDecrease() {
	if (missile_count > 1) {
		missile_count -= 1;
		return true;
	}
	else if (missile_count == 1) {
		missile_count -= 1;
		haveTreasure = false;
		return true;
	}
	else {
		return false;
	}
}

void Person::reset() {
	missile_count = 0;
	isRiding = false;
	haveTreasure = false;
	player_destination.x = 160 - 22;
	player_destination.y = 150 - 31;
}

Person::~Person() {
	SDL_DestroyTexture(player_texture);
}