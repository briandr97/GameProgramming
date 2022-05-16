#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_INGAME = 1;
const int PHASE_ENDING = 2;

using namespace std;

class PhaseInterface {
public:
	PhaseInterface() {};
	virtual ~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};