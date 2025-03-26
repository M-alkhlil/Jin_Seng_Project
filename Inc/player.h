#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"  // For CP_Image and input functions
#include "level.h" // For isTileCollider

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE 32

#define FRAME_COUNT_WALK 8
#define FRAME_COUNT_IDLE 8
#define FRAME_COUNT_JUMP 8
#define FRAME_COUNT_RUN 8

#define FRAME_TIME 0.1f         // Animation frame duration (walking, idle, running)
#define FRAME_TIME_JUMP 0.05f   // Faster animation for jumping
#define PLAYER_SPEED 200.0f     // Pixels per second
#define RUNNING_SPEED 400.0f    // Pixels per second when running
#define GRAVITY 580.0f          // Pixels per second squared
#define JUMP_POWER 600.0f       // Initial upward velocity for jump
#define MAX_FALL_SPEED 600.0f   // Terminal velocity

typedef struct {
    float x, y;                 // Position in pixels (center of sprite)
    float velocity_y, velocity_x;           // Vertical velocity (pixels per second)
    CP_Image frames_walk[FRAME_COUNT_WALK];
    CP_Image frames_idle[FRAME_COUNT_IDLE];
    CP_Image frames_jump[FRAME_COUNT_JUMP];
    CP_Image frames_run[FRAME_COUNT_RUN];
    float frametimer;
    int currentframe;
    int currentframe_jump;
    int isMovingRight;
    int isFacingRight;
    int isJumping;
    int isRunning;
    float width, height;        // Rendered size in pixels
    float collision_width;      // Collision box width
    float collision_height;     // Collision box height
    float collision_offset_x;   // Horizontal offset from center
    float collision_offset_y;   // Vertical offset from center to top of collision box
} Player;

void Player_Init(Player* player);
void Player_Update(Player* player, float deltatime);
void Player_Draw(Player* player);

#endif // PLAYER_H