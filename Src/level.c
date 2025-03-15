#include"level.h"
#include"game.h"

CP_Image greenTile = NULL;
CP_Image blueTile = NULL;
CP_Image brownTile = NULL;
CP_Image slope_left = NULL;
CP_Image slope_right = NULL;
CP_Image green_slope_right = NULL;
CP_Image green_slope_left = NULL;
CP_Image blue_slope_right = NULL;
CP_Image blue_slope_left = NULL;
CP_Image green_right = NULL;
CP_Image green_left = NULL;
CP_Image edge_green_right = NULL;
CP_Image edge_green_left = NULL;
CP_Image edge_bottom_right = NULL;
CP_Image edge_bottom_left = NULL;
CP_Image bridge_left = NULL;
CP_Image bridge_middle = NULL;
CP_Image bridge_right = NULL;
//CP_Image sky_right = NULL;
//CP_Image sky_right2 = NULL;
//CP_Image sky_right3 = NULL;
//CP_Image sky_left = NULL;
//CP_Image sky_left2 = NULL;
//CP_Image sky_left3 = NULL;
CP_Image green_bottom = NULL;
CP_Image edge_left_bottom = NULL;
CP_Image middle_green = NULL;
CP_Image willows = NULL;
CP_Image Ridges = NULL;
CP_Image Bushes = NULL;
CP_Image Bushes2 = NULL;

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,16,16,16,17,0,0,14,13,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,15,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,15,16,16,16,17,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,15,16,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,11,0,0,0,0,0,0,0,0,0,14,10,3,9},
	{6,2,2,13,0,0,0,14,2,2,2,2,2,13,0,0,0,0,14,2,2,2,2,2,2,7,11,0,0,0,0,0,0,0,0,0,12,1,1,1},
	{22,22,22,20,0,0,0,21,22,22,22,22,22,20,0,0,0,0,21,22,22,22,22,22,22,22,20,0,0,0,0,0,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,1,1,1},
	{0,0,0,15,16,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,10,3,28,3,9,13,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,1,1,1,1,1,11,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,1,1,1,1,1,11,0,0,0,0,12,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,4,2,2,10,9,2,2,2,13,0,0,0,0,12,1,1,1,1,1,11,0,0,0,0,12,1,1,1},
	{2,10,9,2,5,0,0,0,0,0,0,4,7,1,1,1,1,1,1,1,11,0,0,0,0,12,1,1,1,1,1,11,0,0,0,0,12,1,1,1},
	{1,1,1,1,6,5,0,0,0,0,4,7,1,1,1,1,1,1,1,1,11,0,0,0,0,12,1,1,1,1,1,11,0,0,0,0,12,1,1,1},
};
void initializeDecoration(void) {
	tree.x = 1150;
	tree.y = 170;
	ridges.x = 530;
	ridges.y = 550;
	bushes[0].x = 200;
	bushes[0].y = 222;
	bushes[1].x = 320;
	bushes[1].y = 352;
	bushes[2].x = 600;
	bushes[2].y = 605;
	bushes[3].x = 470;
	bushes[3].y = 605;

}
void update_flag(Deco* flag,float deltatime) {
	/*flag->frametimer = 0.0f;*/
	flag->frametimer += CP_System_GetDt();
	if (flag->frametimer >= frametime) {
		flag->frametimer = 0.0f; // Reset timer
		flag->currentframe = (flag->currentframe + 1) % framecount; // Loop through frames
	}
}
void initializeLevel(void) {
	greenTile = CP_Image_Load("Assets/Tile/Tile_02.png");
	blueTile = CP_Image_Load("Assets/Tile/Tile_40.png");
	brownTile = CP_Image_Load("Assets/Tile/Tile_12.png");
	slope_left = CP_Image_Load("Assets/Tile/Tile_47.png");
	slope_right = CP_Image_Load("Assets/Tile/Tile_48.png");
	green_slope_right = CP_Image_Load("Assets/Tile/Tile_58.png");
	green_slope_left = CP_Image_Load("Assets/Tile/Tile_57.png");
	blue_slope_right = CP_Image_Load("Assets/Tile/Tile_20.png");
	blue_slope_left = CP_Image_Load("Assets/Tile/Tile_50.png");
	green_right = CP_Image_Load("Assets/Tile/Tile_13.png");
	green_left = CP_Image_Load("Assets/Tile/Tile_11.png");
	edge_green_right = CP_Image_Load("Assets/Tile/Tile_03.png");
	edge_green_left = CP_Image_Load("Assets/Tile/Tile_01.png");
	bridge_left= CP_Image_Load("Assets/Tile/Tile_32.png");
	bridge_middle = CP_Image_Load("Assets/Tile/Tile_33.png");
	bridge_right = CP_Image_Load("Assets/Tile/Tile_34.png");
	/*sky_right = CP_Image_Load("Assets/Tile/Tile_46.png");
	sky_right2 = CP_Image_Load("Assets/Tile/Tile_45.png");
	sky_left = CP_Image_Load("Assets/Tile/Tile_36.png");
	sky_left2 = CP_Image_Load("Assets/Tile/Tile_37.png");*/
	edge_bottom_right = CP_Image_Load("Assets/Tile/Tile_23.png");
	edge_bottom_left = CP_Image_Load("Assets/Tile/Tile_21.png");
	green_bottom = CP_Image_Load("Assets/Tile/Tile_22.png");
	/*sky_left3 = CP_Image_Load("Assets/Tile/Tile_38.png");
	sky_right3 = CP_Image_Load("Assets/Tile/Tile_44.png");*/
	edge_left_bottom = CP_Image_Load("Assets/Tile/Tile_18.png");
	middle_green = CP_Image_Load("Assets/Tile/Tile_60.png");
	willows = CP_Image_Load("Assets/Willows/3.png");
	Ridges = CP_Image_Load("Assets/Ridges/4_resized.png");
	Bushes = CP_Image_Load("Assets/Bushes/5.png");
	Bushes2 = CP_Image_Load("Assets/Bushes/1.png");
	initializeDecoration();
}
void flag_init(Deco* flag) {
	flag->frame_flag[0] = CP_Image_Load("Assets/Flag/Flag_Frame_1.png");
	flag->frame_flag[1] = CP_Image_Load("Assets/Flag/Flag_Frame_2.png");
	flag->frame_flag[2] = CP_Image_Load("Assets/Flag/Flag_Frame_3.png");
	flag->frame_flag[3] = CP_Image_Load("Assets/Flag/Flag_Frame_4.png");
	for (int i = 0; i < framecount; i++) {
		flag[i].frametimer = 0.0f;
		flag[i].currentframe = 0;
	}
}

void drawMap(void) {
		for (int row = 0; row < MAP_HEIGHT; row++) {
			for (int col = 0; col < MAP_WIDTH; col++) {
				int tileType = map[row][col];
				float x = (col) * TILE_SIZE+16;
				float y = (row) * TILE_SIZE+16;

				CP_Image tileToDraw = NULL;
				switch (tileType) {
				case 1: tileToDraw = brownTile; break;
				case 2: tileToDraw = greenTile; break;
				case 3: tileToDraw = blueTile; break;
				case 4: tileToDraw = slope_left; break;
				case 5: tileToDraw = slope_right; break;
				case 6: tileToDraw = green_slope_right; break;
				case 7: tileToDraw = green_slope_left; break;
				case 8: tileToDraw = green_slope_right; break;
				case 9: tileToDraw = blue_slope_left; break;
				case 10: tileToDraw = blue_slope_right; break;
				case 11: tileToDraw = green_right; break;
				case 12: tileToDraw = green_left; break;
				case 13: tileToDraw = edge_green_right; break;
				case 14: tileToDraw = edge_green_left; break;
				case 15: tileToDraw = bridge_left; break;
				case 16: tileToDraw = bridge_middle; break;
				case 17: tileToDraw = bridge_right; break;
				/*case 18: tileToDraw = sky_right; break;
				case 19: tileToDraw = sky_left; break;*/
				case 20: tileToDraw = edge_bottom_right; break;
				case 21: tileToDraw = edge_bottom_left; break;
				case 22: tileToDraw = green_bottom; break;
				/*case 23: tileToDraw = sky_left2; break;
				case 24: tileToDraw = sky_right2; break;
				case 25: tileToDraw = sky_left3; break;
				case 26: tileToDraw = sky_right3; break;*/
				case 27: tileToDraw = edge_left_bottom; break;
				case 28: tileToDraw = middle_green; break;
				default: continue; // Skip empty tiles
				}
				CP_Image_Draw(tileToDraw, x, y, TILE_SIZE, TILE_SIZE, 255);
			}
		}
	}
void drawFlag(Deco *flag,float x, float y, float width, float height) {
	CP_Image_Draw(flag->frame_flag[flag->currentframe], x, y, width, height, 255);
}

void drawDecoration(void) {
	CP_Image_Draw(willows, tree.x, tree.y, 398, 366, 255);
	CP_Image_Draw(Ridges, ridges.x, ridges.y, 195, 183, 255);
	CP_Image_Draw(Bushes, bushes[0].x, bushes[0].y, 100, 73, 255);
	CP_Image_Draw(Bushes2, bushes[1].x, bushes[1].y, 100, 73, 255);
	CP_Image_Draw(Bushes, bushes[2].x, bushes[2].y, 100, 73, 255);
	CP_Image_Draw(Bushes, bushes[3].x, bushes[3].y, -100, 73, 255);
	drawFlag(&flag,1000, 500, 100, 100);
	drawFlag(&flag, 200, 500, 100, 100);
	drawFlag(&flag, 1200, 300, 100, 100);
	drawFlag(&flag, 620, 335, 100, 100);
}
void drawLevel(void) {
	drawDecoration();
	drawMap();
}
void exitLevel(void) {
	CP_Image_Free(&greenTile);
	CP_Image_Free(&brownTile);
	CP_Image_Free(&blueTile);
}