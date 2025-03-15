#ifndef LEVEL_H
#define LEVEL_H

#include"cprocessing.h"

#define Tile_Size 50
#define NUM_TILES 30
typedef struct {
	float x;
	float y;
}Tile;

Tile tile[NUM_TILES];
void initializeLevel(void);
void drawLevel(void);
void exitLevel(void);
#endif