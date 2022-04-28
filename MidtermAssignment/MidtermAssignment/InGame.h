#pragma once
#include "common.h"
#include "Person.h"
#include "Tank.h"
#include "Treasure.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;
extern Mix_Music* Ending_music;
extern Mix_Chunk* shooting_sound;
extern Mix_Chunk* riding_sound;
extern Mix_Chunk* treasure_sound;

class InGame {
private:

	//�׸�-���
	SDL_Texture* bg_texture;
	SDL_Rect bg_source;
	SDL_Rect bg_destination;

	Person *player; //���
	Tank *tank; //��ũ
	Treasure* treasure; //����

	//���
	vector<direction> arrow_input;
	bool cur_space_state;
	bool pre_space_state;
	direction key_direction;

public:
	InGame();
	void HandleEvents();
	void Update();
	void Render();
	void Shooting(direction d);
	void Reset();
	~InGame();
	
};