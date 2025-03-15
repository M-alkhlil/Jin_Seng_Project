#include"game.h"
#include"cprocessing.h"
#include"splashscreen.h"


int main(void) {
	//CP_Engine_SetNextGameState(InitializeGame, UpdateGame, ExitGame);
	CP_System_SetWindowSize(screen_width, screen_height);
	CP_System_SetFrameRate(60);
	CP_Engine_SetNextGameState(InitializeSplashScreen, UpdateSplashScreen, ExitSplashScreen);

	CP_Engine_Run();
	return 0;
}