#ifndef GAME_H
#define GAME_H
#include<cprocessing.h>
#define screen_width 1280
#define screen_height 736
#define Frame_Count_walk 8
#define Frame_Count_idle 8
#define Frame_Count_jump 8
#define Frame_Count_run 8
#define frame_time 0.1
#define frame_time_jump 0.1
#define player_speed 200.f
#define running_speed 400.f
#define gravity 1000.0f
#define jumpPower 50.f
#define fall_multiplier 2.5f
#define maxFallSpeed 800.0f


//typedef struct {
//	CP_Image frames_walk[Frame_Count_walk];
//	CP_Image frames_idle[Frame_Count_idle];
//	CP_Image frames_jump[Frame_Count_jump];
//	CP_Image frames_run[Frame_Count_run];
//	float x, y;
//	float width, height;
//	float velocity_y;
//	float velocity_x;
//	float frametimer;
//	int onGround;
//	int currentframe;
//	int currentframe_jump;
//	int isMovingRight;
//	int isFacingRight;
//	int isJumping;
//	int isRunning;
//	float jumpspeed;
//}Player;

 void InitializeGame(void);
void UpdateGame(void);
void ExitGame(void);

#endif

 
