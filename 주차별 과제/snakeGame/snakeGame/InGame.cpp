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

	font = TTF_OpenFont("../../Resources/paybooc Bold.ttf", 50);
	blue = { 0,50,200,0 };
	SDL_Surface *game_over_surface = TTF_RenderText_Blended(font, "GAME OVER", blue);
	game_over_texture = SDL_CreateTextureFromSurface(g_renderer, game_over_surface);
	game_over_text = { 0,0,game_over_surface->w ,game_over_surface->h };


	direction = -1;
	srand(time(NULL));
	game_over = false;
	game_over_click = false;
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
			if (event.key.keysym.sym == SDLK_LEFT) {
				if(direction!=RIGHT)
					direction = LEFT;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				if (direction != LEFT)
					direction = RIGHT;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				if (direction != DOWN)
					direction = UP;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				if (direction != UP)
					direction = DOWN;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				printf("왼쪽 마우스 눌림\n");
				if (game_over) {
					g_current_game_phase = PHASE_ENDING;
					game_over_click = true;
				}
					
			}
		}
	}
}

void InGame::Update() {
	if (game_over)
		return;

	//item random drop
	randomX = ((rand() % 900) / 10) * 10;
	randomY = ((rand() % 500) / 10) * 10;
	if (item_exist == false) {
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == randomX && (*iter).y == randomY) {
				randomX = ((rand() % 900) / 10) * 10;
				randomY = ((rand() % 500) / 10) * 10;
			}
			else
				continue;
		}
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

	//snake position check
		//1. out of window
	if ((snake.front().x < 0) || (snake.front().x >= 900) || (snake.front().y < 0) || (snake.front().y >= 500)) {
		game_over = true;
		snake.front().x -= tempX;
		snake.front().y -= tempY;
	}
		//2. crash with body
	int headX = snake.front().x;
	int headY = snake.front().y;
	for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
		if ((*iter).x == headX && (*iter).y == headY) {
			game_over = true;
			snake.front().x -= tempX;
			snake.front().y -= tempY;
		}
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

	game_over_destination = { bg_destination.w / 2 - game_over_text.w / 2, bg_destination.h / 2 - game_over_text.h / 2, game_over_text.w, game_over_text.h };
	if(game_over)
		SDL_RenderCopy(g_renderer, game_over_texture, &game_over_text, &game_over_destination);

	if (game_over_click)
		Reset();

	SDL_RenderPresent(g_renderer);
}

void InGame::Reset() {
	snake.clear();
	snake.push_front({ 0,0,WIDTH,HEIGHT });
	direction = STOP;
	game_over = false;
	game_over_click = false;
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg_destination);
	SDL_RenderCopy(g_renderer, item_texture, &item_source, &item_destination);
	SDL_RenderCopy(g_renderer, snake_texture, &snake_source, &(snake.front()));
}