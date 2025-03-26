#include "player.h"
#include <stdio.h>

void Player_Init(Player* player) {
    // Load animation frames (unchanged)
    player->frames_walk[0] = CP_Image_Load("Assets/walk/frame_0.png");
    player->frames_walk[1] = CP_Image_Load("Assets/walk/frame_1.png");
    player->frames_walk[2] = CP_Image_Load("Assets/walk/frame_2.png");
    player->frames_walk[3] = CP_Image_Load("Assets/walk/frame_3.png");
    player->frames_walk[4] = CP_Image_Load("Assets/walk/frame_4.png");
    player->frames_walk[5] = CP_Image_Load("Assets/walk/frame_5.png");
    player->frames_walk[6] = CP_Image_Load("Assets/walk/frame_6.png");
    player->frames_walk[7] = CP_Image_Load("Assets/walk/frame_7.png");

    player->frames_idle[0] = CP_Image_Load("Assets/idle/frame_0.png");
    player->frames_idle[1] = CP_Image_Load("Assets/idle/frame_1.png");
    player->frames_idle[2] = CP_Image_Load("Assets/idle/frame_2.png");
    player->frames_idle[3] = CP_Image_Load("Assets/idle/frame_3.png");
    player->frames_idle[4] = CP_Image_Load("Assets/idle/frame_4.png");
    player->frames_idle[5] = CP_Image_Load("Assets/idle/frame_5.png");
    player->frames_idle[6] = CP_Image_Load("Assets/idle/frame_6.png");
    player->frames_idle[7] = CP_Image_Load("Assets/idle/frame_7.png");

    player->frames_jump[0] = CP_Image_Load("Assets/jump/frame_0.png");
    player->frames_jump[1] = CP_Image_Load("Assets/jump/frame_1.png");
    player->frames_jump[2] = CP_Image_Load("Assets/jump/frame_2.png");
    player->frames_jump[3] = CP_Image_Load("Assets/jump/frame_3.png");
    player->frames_jump[4] = CP_Image_Load("Assets/jump/frame_4.png");
    player->frames_jump[5] = CP_Image_Load("Assets/jump/frame_5.png");
    player->frames_jump[6] = CP_Image_Load("Assets/jump/frame_6.png");
    player->frames_jump[7] = CP_Image_Load("Assets/jump/frame_7.png");

    player->frames_run[0] = CP_Image_Load("Assets/run/frame_0.png");
    player->frames_run[1] = CP_Image_Load("Assets/run/frame_1.png");
    player->frames_run[2] = CP_Image_Load("Assets/run/frame_2.png");
    player->frames_run[3] = CP_Image_Load("Assets/run/frame_3.png");
    player->frames_run[4] = CP_Image_Load("Assets/run/frame_4.png");
    player->frames_run[5] = CP_Image_Load("Assets/run/frame_5.png");
    player->frames_run[6] = CP_Image_Load("Assets/run/frame_6.png");
    player->frames_run[7] = CP_Image_Load("Assets/run/frame_7.png");

    player->x = 50;
    player->y = 580;
    player->velocity_y = 0.0f;
    player->frametimer = 0.0f;
    player->currentframe = 0;
    player->currentframe_jump = 0;
    player->isMovingRight = 0;
    player->isFacingRight = 1;
    player->isJumping = 0;
    player->isRunning = 0;
    player->width = 150;
    player->height = 150;
    player->collision_width = 5;
    player->collision_height = 140;  // Increased to nearly match sprite height
    player->collision_offset_x = 5;
    player->collision_offset_y = 5;
}

void Player_Update(Player* player, float deltatime) {
    // Reset movement flags
    player->isRunning = 0;
    player->isMovingRight = 0;

    // Determine move speed
    float moveSpeed = PLAYER_SPEED;
    if (CP_Input_KeyDown(KEY_SPACE) && (CP_Input_KeyDown(KEY_D) || CP_Input_KeyDown(KEY_A))) {
        player->isRunning = 1;
        moveSpeed = RUNNING_SPEED;
    }

    // Horizontal movement
    float new_x = player->x;
    if (CP_Input_KeyDown(KEY_D)) {
        new_x += moveSpeed * deltatime;
        player->isMovingRight = 1;
        player->isFacingRight = 1;
    }
    else if (CP_Input_KeyDown(KEY_A)) {
        new_x -= moveSpeed * deltatime;
        player->isMovingRight = 1;
        player->isFacingRight = 0;
    }

    // Apply gravity
    player->velocity_y += GRAVITY * deltatime;

    // Jump (only if on ground)
    if (CP_Input_KeyTriggered(KEY_W) && !player->isJumping) {
        player->velocity_y = -JUMP_POWER;
        player->isJumping = 1;
    }

    // Limit fall speed
    if (player->velocity_y > MAX_FALL_SPEED) {
        player->velocity_y = MAX_FALL_SPEED;
    }

    // Apply vertical movement
    float new_y = player->y + player->velocity_y * deltatime;

    // Collision detection
    int player_left = (int)(new_x - player->collision_width + player->collision_offset_x) / TILE_SIZE;
    int player_right = (int)(new_x + player->collision_width + player->collision_offset_x) / TILE_SIZE;
    int player_top = (int)(new_y - player->collision_height / 8 + player->collision_offset_y) / TILE_SIZE;  // Adjusted to center collision box
    int player_bottom = (int)(new_y + player->collision_height / 2 + player->collision_offset_y) / TILE_SIZE;

    // Horizontal collision
    if (new_x != player->x) {
        if (player->isFacingRight) { // Moving right
            if (isTileCollider(player_right, player_top)) {
                new_x = player_right * TILE_SIZE - player->collision_width - player->collision_offset_x - 1;
            }
        }
        else { // Moving left
            if (isTileCollider(player_left, player_top)) {
                new_x = (player_left + 1) * TILE_SIZE - player->collision_offset_x + player->collision_width;
            }
        }
    }

    // Vertical collision
    if (new_y != player->y) {
        if (player->velocity_y > 0) { // Falling
            if (isTileCollider(player_left, player_bottom) || isTileCollider(player_right, player_bottom)) {
                new_y = player_bottom * TILE_SIZE - player->collision_height / 2 - player->collision_offset_y - 1;
                player->velocity_y = 0;
                player->isJumping = 0;
            }
        }
        else if (player->velocity_y < 0) { // Jumping upward - Top collision
            if (isTileCollider(player_left, player_top) || isTileCollider(player_right, player_top)) {
                new_y = (player_top + 1) * TILE_SIZE + player->collision_height / 2 - player->collision_offset_y;
                player->velocity_y = 0;  // Stop upward movement when hitting ceiling
            }
        }
    }

    // Update position
    player->x = new_x;
    player->y = new_y;

    // Boundary checks (screen edges)
    if (player->x < player->collision_width) player->x = player->collision_width;
    if (player->x > SCREEN_WIDTH - player->collision_width) player->x = SCREEN_WIDTH - player->collision_width;
    if (player->y > SCREEN_HEIGHT - player->collision_height / 2 + player->collision_offset_y) {
        player->y = SCREEN_HEIGHT - player->collision_height / 2 + player->collision_offset_y;
        player->velocity_y = 0;
        player->isJumping = 0;
    }

    // Update animation
    player->frametimer += deltatime;
    if (player->isJumping) {
        if (player->frametimer >= FRAME_TIME_JUMP) {
            player->frametimer = 0.0f;
            player->currentframe_jump = (player->currentframe_jump + 1) % FRAME_COUNT_JUMP;
        }
    }
    else if (player->isRunning) {
        if (player->frametimer >= FRAME_TIME) {
            player->frametimer = 0.0f;
            player->currentframe = (player->currentframe + 1) % FRAME_COUNT_RUN;
        }
    }
    else if (player->isMovingRight) {
        if (player->frametimer >= FRAME_TIME) {
            player->frametimer = 0.0f;
            player->currentframe = (player->currentframe + 1) % FRAME_COUNT_WALK;
        }
    }
    else {
        if (player->frametimer >= FRAME_TIME) {
            player->frametimer = 0.0f;
            player->currentframe = (player->currentframe + 1) % FRAME_COUNT_IDLE;
        }
    }
}

void Player_Draw(Player* player) {
    player->width = player->isFacingRight ? 150 : -150;
    player->height = 150;
    if (player->isJumping) {
        CP_Image_Draw(player->frames_jump[player->currentframe_jump], player->x, player->y, player->width, player->height, 255);
    }
    else if (player->isRunning) {
        CP_Image_Draw(player->frames_run[player->currentframe], player->x, player->y, player->width, player->height, 255);
    }
    else if (player->isMovingRight) {
        CP_Image_Draw(player->frames_walk[player->currentframe], player->x, player->y, player->width, player->height, 255);
    }
    else {
        CP_Image_Draw(player->frames_idle[player->currentframe], player->x, player->y, player->width, player->height, 255);
    }
}