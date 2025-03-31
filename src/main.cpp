#include "game.h"
#include "player.h"

int main ()
{
	
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Simple Multiplayer");

	SearchAndSetResourceDir("resources");


	// Bullet logic
	BulletManager bulletManager;

	// Player logic
	PlayerManager playerManager;
	playerManager.addPlayer(DEFAULT_ID, DEFAULT_POSITION, DEFAULT_HEALTH, DEFAULT_SPEED);
    float fireRate = 0.5f;
    float lastFired = 0.0f;

	// run the loop until the user presses ESCAPE or presses the Close button on the window
	while (!WindowShouldClose())
	{
		//deltaTime(in seconds since last frame)
		float dt = GetFrameTime();

		// Update Players
		playerManager.updatePlayers(dt);


		// if player ID is 0 (main player)
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			if((GetTime() - lastFired) >= fireRate){
			//If enough time has passed since last shot
				bulletManager.addBullet(
					playerManager.getPlayerPosition(0), // Current Pos of player is bullets start pos
					GetMousePosition() // target pos
				);
				//Last fired time update
				lastFired = GetTime();
			}
		}	

		// Update bullets
		bulletManager.updateBullets(dt);	

		// drawing
		BeginDrawing();
	    ClearBackground(WHITE);
        EndDrawing();
	}


	CloseWindow();
	return 0;
}
