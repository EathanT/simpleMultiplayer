#include "game.h"
#include "player.h"

int main()
{
    // Configure window settings
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Improved Multiplayer");
    SetTargetFPS(60);  // Set target FPS for consistent performance

    // Initialize game engine
    GameEngine gameManager;
    
    // Main game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        // Update game state
        gameManager.updateGame(dt);
        
        // Render game
        BeginDrawing();
            ClearBackground(RAYWHITE);
            gameManager.renderGame();
            
            // Display controls
            DrawText("WASD: Move | MOUSE: Aim | LEFT CLICK: Shoot", 10, 10, 20, DARKGRAY);
            DrawFPS(1200, 10);
        EndDrawing();
    }

    // Cleanup and exit
    CloseWindow();
    return 0;
}