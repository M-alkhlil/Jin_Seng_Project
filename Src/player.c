#include"player.h"
#include"collision.h"

void Player_Init(Player*player) {
	
	player->frames_walk[0] = CP_Image_Load("Assets/walk/frame_0.png");
	player->frames_walk[1] = CP_Image_Load("Assets/walk/frame_1.png");
	player->frames_walk[2] = CP_Image_Load("Assets/walk/frame_2.png");
	player->frames_walk[3] = CP_Image_Load("Assets/walk/frame_3.png");
	player->frames_walk[4] = CP_Image_Load("Assets/walk/frame_4.png");
	player->frames_walk[5] = CP_Image_Load("Assets/walk/frame_5.png");
	player->frames_walk[6] = CP_Image_Load("Assets/walk/frame_6.png");
	player->frames_walk[7] = CP_Image_Load("Assets/walk/frame_7.png");
	//idle
	player->frames_idle[0] = CP_Image_Load("Assets/idle/frame_0.png");
	player->frames_idle[1] = CP_Image_Load("Assets/idle/frame_1.png");
	player->frames_idle[2] = CP_Image_Load("Assets/idle/frame_2.png");
	player->frames_idle[3] = CP_Image_Load("Assets/idle/frame_3.png");
	player->frames_idle[4] = CP_Image_Load("Assets/idle/frame_4.png");
	player->frames_idle[5] = CP_Image_Load("Assets/idle/frame_5.png");
	player->frames_idle[6] = CP_Image_Load("Assets/idle/frame_6.png");
	player->frames_idle[7] = CP_Image_Load("Assets/idle/frame_7.png");
	//jumping
	player->frames_jump[0] = CP_Image_Load("Assets/jump/frame_0.png");
	player->frames_jump[1] = CP_Image_Load("Assets/jump/frame_1.png");
	player->frames_jump[2] = CP_Image_Load("Assets/jump/frame_2.png");
	player->frames_jump[3] = CP_Image_Load("Assets/jump/frame_3.png");
	player->frames_jump[4] = CP_Image_Load("Assets/jump/frame_4.png");
	player->frames_jump[5] = CP_Image_Load("Assets/jump/frame_5.png");
	player->frames_jump[6] = CP_Image_Load("Assets/jump/frame_6.png");
	player->frames_jump[7] = CP_Image_Load("Assets/jump/frame_7.png");
	//running
	player->frames_run[0] = CP_Image_Load("Assets/run/frame_0.png");
	player->frames_run[1] = CP_Image_Load("Assets/run/frame_1.png");
	player->frames_run[2] = CP_Image_Load("Assets/run/frame_2.png");
	player->frames_run[3] = CP_Image_Load("Assets/run/frame_3.png");
	player->frames_run[4] = CP_Image_Load("Assets/run/frame_4.png");
	player->frames_run[5] = CP_Image_Load("Assets/run/frame_5.png");
	player->frames_run[6] = CP_Image_Load("Assets/run/frame_6.png");
	player->frames_run[7] = CP_Image_Load("Assets/run/frame_7.png");



	player->x = 150;//screen_width / 2.0f - 85 / 2.0f;
		player->y = 470;//screen_height - 200;
	player->frametimer = 0.0f;
	player->currentframe = 0;
	player->currentframe_jump = 0;
	player->isMovingRight = 0;
	player->isFacingRight = 1;
	player->isJumping = 0;
	
}
void Player_Update(Player* player, float deltatime) {

	player->isRunning = 0;
	player->isMovingRight = 0;
	float movespeed = player_speed;
	//running
	if (CP_Input_KeyDown(KEY_SPACE) && (CP_Input_KeyDown(KEY_D) || CP_Input_KeyDown(KEY_A))) {
		player->isRunning = 1;
		movespeed = running_speed;
	}
	//moving right
	if (CP_Input_KeyDown(KEY_D)) {
		if (!player->isJumping) {
			player->jumpspeed = movespeed;
		}
		player->x += (player->isJumping ? player->jumpspeed:movespeed)* deltatime;
		player->isMovingRight = 1;
		player->isFacingRight = 1;
	}
	//moving left
	else if (CP_Input_KeyDown(KEY_A)) {
		if (!player->isJumping) {
			player->jumpspeed = movespeed;
		}
		player->x -= (player->isJumping ? player->jumpspeed : movespeed) * deltatime;
		player->isMovingRight = 1;
		player->isFacingRight = 0;
	}

	/*m.alkhlil*/
	// Apply Boundary Check for X position
	if (player->x < 32) {
		player->x = 32; // Prevent moving off the left edge
	}
	if (player->x > screen_width-32) {
		player->x = screen_width-32; // Prevent moving off the right edge
	}



	//jumping
	if (CP_Input_KeyTriggered(KEY_W) && !player->isJumping) {
		player->velocity_y = -jumpPower;
		player->isJumping = 1;
		player->jumpspeed = movespeed;
	  }
	
	if (player->isJumping) {
		if (player->velocity_y < 0) {
			// Going up: apply normal gravity
			player->velocity_y += gravity * deltatime;
		}
		else {
			// Falling: apply increased gravity for snappier falls
			player->velocity_y += gravity * fall_multiplier * deltatime;
		}
	}

	// Limit max fall speed
	if (player->velocity_y > maxFallSpeed) {
		player->velocity_y = maxFallSpeed;
	}

	// Apply movement
	player->y += player->velocity_y * deltatime;
	// Check ground collision
	if (player->y >= screen_height - 200) { // Adjust based on your ground level
		player->y = screen_height - 200;
		player->velocity_y = 0;
		player->isJumping = 0;
	}

	//update animation
	player->frametimer += deltatime;
	if (player->isJumping) {
		if (player->frametimer >= frame_time_jump) {
			player->frametimer = 0.0f;
			player->currentframe_jump = (player->currentframe_jump + 1) % Frame_Count_jump;
		}
	}
	else if (player->isRunning) {
		if (player->frametimer >= frame_time) {
			player->frametimer = 0.0f;
			player->currentframe = (player->currentframe + 1) % Frame_Count_walk;
		}
	}
	else if (player->isMovingRight) {
		if (player->frametimer >= frame_time) {
			player->frametimer = 0.0f;
			player->currentframe = (player->currentframe + 1) % Frame_Count_walk;
		}
	}
	else {
		if (player->frametimer >= frame_time) {
			player->frametimer = 0.0f;
			player->currentframe = (player->currentframe + 1) % Frame_Count_idle;
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
	else CP_Image_Draw(player->frames_idle[player->currentframe], player->x, player->y, player->width, player->height, 255);
}