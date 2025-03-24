#include "bullet.h"


// player 
void drawPlayer(Vector2 p1){
	DrawRectangle(p1.x,p1.y,20,20,BLUE);
}



int main ()
{
	
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	// store player position in center of screen	
	Vector2 p1 = {GetScreenWidth()/2.0f,GetScreenHeight()/2.0f};

	//Bullet logic
	BulletManager bulletManager;

	//Fire-rate control
	float fireRate = 0.5f;
	float lastFired = 0.0f;


	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		//deltaTime(in seconds since last frame)
		float dt = GetFrameTime();

		// Player Movement	
	        if (IsKeyDown(KEY_D)) p1.x += 250.0f * dt;
                if (IsKeyDown(KEY_A)) p1.x -= 250.0f * dt;
                if (IsKeyDown(KEY_W)) p1.y -= 250.0f * dt;
                if (IsKeyDown(KEY_S)) p1.y += 250.0f * dt;

		// Firing bullets
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			//If enough time has passed since last shot
			if((GetTime() - lastFired)>= fireRate){
				bulletManager.addBullet(
					p1, //start pos
					GetMousePosition(), // target pos
					300.0f, //bullet speed(pixels/sec)
					5.0f, // bullet radius
					600.0f, // bullet max travel dist
					BulletType::Normal	
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

          		drawPlayer(p1);
			bulletManager.drawBullets();
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
        	EndDrawing();
	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
