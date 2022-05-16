#include "InGame.h"

InGame::InGame() {
	printf("InGame진입\n");
	SDL_Surface* bg_surface = IMG_Load("../../Resources/inGameBg.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,900,500 };
	bg_destination = { 0, 0, bg_source.w, bg_source.h };
	printf("배경 그림 선언\n");
	
	SDL_Surface* snake_surface = IMG_Load("../../Resources/spot.png");
	snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	snake_source = { 0,0,WIDTH,HEIGHT };
	snake.push_front({ 0,0,WIDTH,HEIGHT });
	printf("뱀 그림 선언\n");

	SDL_Surface* item_surface = IMG_Load("../../Resources/item.png");
	item_texture = SDL_CreateTextureFromSurface(g_renderer, item_surface);
	SDL_FreeSurface(item_surface);
	item_source = { 0,0,WIDTH,HEIGHT };
	item_exist = false;
	printf("아이템 그림 선언\n");

	direction = -1;
	srand(time(NULL));
}

InGame::~InGame() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(snake_texture);
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
			else if (event.key.keysym.sym == SDLK_LEFT) {
				direction = LEFT;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				direction = RIGHT;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				direction = UP;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				direction = DOWN;
			}
			break;
		}
	}
}

void InGame::Update() {

	//item random drop
	if (item_exist == false) {
		randomX = ((rand() % 900) / 10) * 10;
		randomY = ((rand() % 500) / 10) * 10;
		item_destination = { randomX, randomY, WIDTH, HEIGHT };
		item_exist = true;
	}

	//snake move
	int tempX = 0;
	int tempY = 0;
	switch (direction) {
	case LEFT:
		tempX = -10;
		tempY = 0;
		break;
	case RIGHT:
		tempX = 10;
		tempY = 0;
		break;
	case UP:
		tempX = 0;
		tempY = -10;
		break;
	case DOWN:
		tempX = 0;
		tempY = 10;
		break;
	default:
		break;
	}
	snake.push_front({ snake.front().x + tempX , snake.front().y + tempY, WIDTH, HEIGHT });
	snake.pop_back();

	//snake item check
	if ((snake.front().x == item_destination.x) && (snake.front().y==item_destination.y)) {
		snake.push_front({ snake.front().x + tempX, snake.front().y + tempY, WIDTH, HEIGHT });
		item_exist = false;
	}
}

void InGame::Render() {
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderCopy(g_renderer, item_texture, &item_source, &item_destination);
	for (auto iter = snake.begin(); iter != snake.end(); iter++) {
		printf("x:%d, y:%d\n", (*iter).x, (*iter).y);
		SDL_RenderCopy(g_renderer, snake_texture, &snake_source, &(*iter));
	}
	printf("반복문 끝\n");
	SDL_RenderPresent(g_renderer);
}