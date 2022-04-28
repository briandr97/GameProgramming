#define _CRT_SECURE_NO_WARNINGS
#include "InGame.h"
#include <atlstr.h>

typedef struct Missile {
	int x;
	int y;
	direction d;
	bool state;
};
void move(Missile* missile, int n) {
	switch (missile->d) {
	case LEFT:
		missile->x -= n;
		break;
	case RIGHT:
		missile->x += n;
		break;
	case UP:
		missile->y -= n;
		break;
	case DOWN:
		missile->y += n;
		break;
	default:
		break;
	}
}
bool checkOut(Missile* missile, int x1, int y1, int x2, int y2) {
	if ((missile->x < (x1 - 100)) ||
		(missile->x > (x2 + 100)) ||
		(missile->y > (y1 - 100)) ||
		(missile->y < (y1 + 100))) {
		missile->state = false;
	}
	return missile->state;
}
vector<Missile> missile; //미사일
SDL_Texture* missile_texture[4];
SDL_Rect missile_source[4];
TTF_Font* font;
SDL_Color blue;
SDL_Texture* count_texture;
SDL_Surface* count_surface;
SDL_Rect count_text;
SDL_Texture* riding_texture;
SDL_Surface* riding_surface;
SDL_Rect riding_text;

InGame::InGame() {
	//그림-배경
	SDL_Surface* bg_surface = IMG_Load("../../Resources/battleMap2.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source = { 0,0,960,900 };
	bg_destination = { 0,0,bg_source.w, bg_source.h };

	//미사일
	SDL_Surface* missile_left_surface = IMG_Load("../../Resources/missile_left.png");
	SDL_Surface* missile_right_surface = IMG_Load("../../Resources/missile_right.png");
	SDL_Surface* missile_up_surface = IMG_Load("../../Resources/missile_up.png");
	SDL_Surface* missile_down_surface = IMG_Load("../../Resources/missile_down.png");
	SDL_SetColorKey(missile_left_surface, SDL_TRUE, SDL_MapRGB(missile_left_surface->format, 255, 255, 255));
	SDL_SetColorKey(missile_right_surface, SDL_TRUE, SDL_MapRGB(missile_right_surface->format, 255, 255, 255));
	SDL_SetColorKey(missile_up_surface, SDL_TRUE, SDL_MapRGB(missile_up_surface->format, 255, 255, 255));
	SDL_SetColorKey(missile_down_surface, SDL_TRUE, SDL_MapRGB(missile_down_surface->format, 255, 255, 255));
	missile_texture[LEFT] = SDL_CreateTextureFromSurface(g_renderer, missile_left_surface);
	missile_texture[RIGHT] = SDL_CreateTextureFromSurface(g_renderer, missile_right_surface);
	missile_texture[UP] = SDL_CreateTextureFromSurface(g_renderer, missile_up_surface);
	missile_texture[DOWN] = SDL_CreateTextureFromSurface(g_renderer, missile_down_surface);
	SDL_FreeSurface(missile_left_surface);
	SDL_FreeSurface(missile_right_surface);
	SDL_FreeSurface(missile_up_surface);
	SDL_FreeSurface(missile_down_surface);
	missile_source[LEFT] = { 0,0,899,277 };
	missile_source[RIGHT] = { 0,0,900,278 };
	missile_source[UP] = { 0,0,277,899 };
	missile_source[DOWN] = { 0,0,277,899 };

	font = TTF_OpenFont("../../Resources/paybooc Bold.ttf", 30);
	blue = { 0,50,200,0 };

	riding_surface = TTF_RenderUTF8_Blended(font, CW2A(L"탑승중", CP_UTF8), blue);
	riding_text = { 0,0,riding_surface->w ,riding_surface->h };
	riding_texture = SDL_CreateTextureFromSurface(g_renderer, riding_surface);

	player = new Person(160, 150); //사람
	tank = new Tank(320, 300); //탱크
	treasure = new Treasure(10, 10); //보물

	// 음악 - 효과음
	shooting_sound = Mix_LoadWAV("../../Resources/kick.wav");
	riding_sound = Mix_LoadWAV("../../Resources/effect_sound.wav");
	treasure_sound = Mix_LoadWAV("../../Resources/treasure_sound.wav");

	key_direction = DOWN;

	cur_space_state = false;
	pre_space_state = false;
}

void InGame::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_RIGHT) {
				Reset();
				game_phase = ENDING;
				Mix_PlayMusic(Ending_music, -1);
			}
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (arrow_input.empty()) {
					arrow_input.emplace_back(LEFT);
				}
				else if (arrow_input.back() != LEFT) {
					arrow_input.emplace_back(LEFT);
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				if (arrow_input.empty()) {
					arrow_input.emplace_back(RIGHT);
				}
				else if (arrow_input.back() != RIGHT) {
					arrow_input.emplace_back(RIGHT);
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				if (arrow_input.empty()) {
					arrow_input.emplace_back(UP);
				}
				else if (arrow_input.back() != UP) {
					arrow_input.emplace_back(UP);
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				if (arrow_input.empty()) {
					arrow_input.emplace_back(DOWN);
				}
				else if (arrow_input.back() != DOWN) {
					arrow_input.emplace_back(DOWN);
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				cur_space_state = true;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT) {
				for (int i = arrow_input.size() - 1; i >= 0; i--) {
					if (arrow_input[i] == LEFT) {
						arrow_input.erase(arrow_input.begin() + i);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				for (int i = arrow_input.size() - 1; i >= 0; i--) {
					if (arrow_input[i] == RIGHT) {
						arrow_input.erase(arrow_input.begin() + i);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				for (int i = arrow_input.size() - 1; i >= 0; i--) {
					if (arrow_input[i] == UP) {
						arrow_input.erase(arrow_input.begin() + i);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				for (int i = arrow_input.size() - 1; i >= 0; i--) {
					if (arrow_input[i] == DOWN) {
						arrow_input.erase(arrow_input.begin() + i);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				cur_space_state = false;
			}
			break;
		default:
			break;
		}
	}
}

void InGame::Update() {
	//발사된 미사일 이동 및 수거
	for (int i = 0; i < 20; i++) {
		if (i < missile.size()) {
			if (missile[i].state == true) {
				switch (missile[i].d) {
				case LEFT:
					missile[i].x -= 20;
					break;
				case RIGHT:
					missile[i].x += 20;
					break;
				case UP:
					missile[i].y -= 20;;
					break;
				case DOWN:
					missile[i].y += 20;;
					break;
				default:
					break;
				}
				if ((missile[i].x > bg_destination.w * 1.2) ||
					(missile[i].x < -50) ||
					(missile[i].y > bg_destination.h * 1.2) ||
					(missile[i].y < -50))
				{
					missile.erase(missile.begin());
				}
			}
			else
				missile.erase(missile.begin());
		}
	}

	//스페이스바 처리
	// 1 - 탱크 스페이스바
	if (tank->nearTank(player->getX(), player->getY())) {
		if (!pre_space_state) {
			if (cur_space_state) {
				if (!player->getRidingState()) {
					player->setRidingState(true);
					arrow_input.clear();
					Mix_PlayChannel(-1, riding_sound, 0);
				}
				else {
					player->setRidingState(false);
					arrow_input.clear();
					Mix_PlayChannel(-1, riding_sound, 0);
				}
			}
		}
		pre_space_state = cur_space_state;
	}

	// 2 - 보물상자 스페이스바
	if (treasure->nearTreasure(player->getX(), player->getY())) {
		if (cur_space_state && !player->getTreasure()) {
			player->pickUpTreasure();
			Mix_PlayChannel(-1, treasure_sound, 0);
			cur_space_state = false;
		}
	}

	//방향키 처리
	if (player->getRidingState()) {
		if (!arrow_input.empty()) {
			Shooting(arrow_input.back());
			key_direction = arrow_input.back();
			arrow_input.clear();
		}
	}
	else {
		if (!arrow_input.empty()) {
			player->move(arrow_input.back());
			player->limit(640, 600);
		}

	}
}

void InGame::Shooting(direction d) {
	int x, y;

	if (!player->missileDecrease())
		return;
	
	switch (d) {
	case LEFT:
		x = tank->getX() - 120;
		y = tank->getY();
		break;
	case RIGHT:
		x = tank->getX() + 40;
		y = tank->getY(); 
		break;
	case UP:
		x = tank->getX();
		y = tank->getY() - 100;
		break;
	case DOWN:
		x = tank->getX();
		y = tank->getY() + 50;
	}
	Missile m = { x, y, d, true };
	missile.emplace_back(m);
	if (missile.size() > 20)
		missile.erase(missile.begin());
	Mix_PlayChannel(-1, shooting_sound, 0);
}

void InGame::Render() {
	//배경
	SDL_Rect bg;
	bg = bg_destination;
	bg.w = (double)bg_destination.w * 0.75;
	bg.h = (double)bg_destination.h * 0.75;
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source, &bg);
	
	//탱크
	tank->show(key_direction);

	//보물
	if (!player->getTreasure())
		treasure->show();

	//플레이어
	player->show();

	//미사일
	SDL_Rect m1;
	direction d1;
	for (int i = 0; i < 20; i++) {
		if ((i < missile.size()) && (missile[i].state)) {
			switch (missile[i].d) {
			case LEFT:
				d1 = LEFT;
				break;
			case RIGHT:
				d1 = RIGHT;
				break;
			case UP:
				d1 = UP;
				break;
			case DOWN:
				d1 = DOWN;
				break;
			default:
				break;
			}
			m1 = { missile[i].x, missile[i].y, missile_source[d1].w / 10, missile_source[d1].h / 10 };
			SDL_RenderCopy(g_renderer, missile_texture[d1], &missile_source[d1], &m1);
		}
	}

	//글자
	//미사일 개수, 탑승여부
	count_surface = TTF_RenderText_Blended(font, to_string(player->getMissileCount()).c_str(), blue);
	count_text = { 0,0,count_surface->w ,count_surface->h };
	count_texture = SDL_CreateTextureFromSurface(g_renderer, count_surface);

	SDL_Rect temp_count;
	temp_count = { 600,550,count_text.w, count_text.h };
	SDL_RenderCopy(g_renderer, count_texture, &count_text, &temp_count);

	SDL_Rect temp_riding;
	temp_riding = { 0,550,riding_text.w, riding_text.h };
	if (player->getRidingState())
		SDL_RenderCopy(g_renderer, riding_texture, &riding_text, &temp_riding);


	SDL_RenderPresent(g_renderer);
}

void InGame::Reset() {
	arrow_input.clear();
	key_direction = DOWN;
	player->reset();
}

InGame::~InGame() {
	delete(player);
	delete(tank);
	//delete(treasure);
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
}