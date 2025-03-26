#include "game.h"
#include"player.h"
#include"level.h"
 CP_Image background;
Player player;
CP_Sound GameSound = NULL;

void startgame(void) {
	CP_Engine_SetNextGameState(InitializeGame, UpdateGame, ExitGame);
}

void InitializeGame(void) {
	CP_System_SetWindowSize(screen_width, screen_height);
	CP_System_SetFrameRate(60);
	background = CP_Image_Load("Assets/Background.png");
	initializeLevel();
	Player_Init(&player);
	flag_init(&flag);
	GameSound = CP_Sound_Load("Assets/gamesound.mp3");
	CP_Sound_PlayAdvanced(GameSound, 1.0f, 1.0f, 1, 0);
	
}
void UpdateGame(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(background, screen_width /2.0f, screen_height/2.0f, screen_width, screen_height, 255);
	//player movement
	float deltatime = CP_System_GetDt();
	Player_Update(&player, deltatime);
	
	update_flag(&flag,deltatime);
	drawLevel();
	Player_Draw(&player);
}
void ExitGame(void) {
	CP_Image_Free(&background);
	for (int i = 0; i < Frame_Count_walk; i++) {
		CP_Image_Free(&player.frames_walk[i]);
	}
	for (int i = 0; i < Frame_Count_idle; i++) {
		CP_Image_Free(&player.frames_idle[i]);
	}
	exitLevel();
}