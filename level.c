#include"level.h"

CP_Image blueTile = NULL;
CP_Image greenTile = NULL;
CP_Image brownTile = NULL;

void initializeLowerGround(void) {
	const float lowerX = 25;
	const float lowerY = 700;

	for (int i = 0; i < 30; i++) {
		tile[i].x = lowerX + (i * Tile_Size);
		tile[i].y = lowerY;
	}
}
void initializeLowerGround2(void) {
	 float lower2X = 25;
	 float lower2Y = 750;

	for (int i = 0; i < 30; i++) {
		tile[i].x = lower2X + (i * Tile_Size);
		tile[i].y = lower2Y;
	}
}

void initializeLevel(void) {
	blueTile = CP_Image_Load("Assets/Tile/Tile_10");
	greenTile = CP_Image_Load("Assets/Tile/Tile_02");
	brownTile = CP_Image_Load("Assets/Tile/Tile_12");
	initializeLowerGround();
	initializeLowerGround2();
}

void drawLowerGround(void) {
	for (int i = 0; i < 4; i++) {
		CP_Image_Draw(blueTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}
	for (int i = 4; i < 6; i++) {
		CP_Image_Draw(greenTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}
	for (int i = 9; i < 15; i++) {
		CP_Image_Draw(greenTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}

}

void drawLowerGround2(void) {
	for (int i = 0; i < 4; i++) {
		CP_Image_Draw(brownTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}
	for (int i = 4; i < 6; i++) {
		CP_Image_Draw(brownTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}
	for (int i = 9; i < 15; i++) {
		CP_Image_Draw(brownTile, tile[i].x, tile[i].y, Tile_Size, Tile_Size, 255);
	}
}
void drawLevel(void) {
	drawLowerGround();
	drawLowerGround2();
}

void levelExit(void) {
	CP_Image_Free(&blueTile);
	CP_Image_Free(&greenTile);
	CP_Image_Free(&brownTile);

}