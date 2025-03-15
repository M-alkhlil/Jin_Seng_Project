#ifndef LEVEL_H
#define LEVEL_H

#include"cprocessing.h"

#define TILE_SIZE 32.0f
#define MAP_WIDTH 40
#define MAP_HEIGHT 23
#define framecount 4
#define frametime 0.2

typedef struct {
	CP_Image frame_flag[framecount];
	float frametimer;
	int currentframe;
	float x;
	float y;
}Deco;

Deco tree;
Deco ridges;
Deco bushes[4];
Deco flag;
extern int map[MAP_HEIGHT][MAP_WIDTH];
void initializeLevel(void);
void flag_init(Deco* flag);
void update_flag(Deco *flag,float deltatime);
void drawLevel(void);
void exitLevel(void);
#endif
