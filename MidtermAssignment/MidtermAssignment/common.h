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

enum phase { INTRO, INGAME, ENDING };
enum direction {LEFT, RIGHT, UP, DOWN};