#pragma once

// From Game Coordinate(meter) to Window Coordinate(pixel)
int G2W_X(float g_x);
int G2W_Y(float g_y);
extern float G2W_Scale;

// From Window Coordinate(pixel) to Game Coordinate(meter)
float W2G_X(int w_x);
float W2G_Y(int w_y);
extern float W2G_Scale;

extern float small_ver;
extern float big_ver;
void big2small();
void small2big();