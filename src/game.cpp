#include "game.h"

void GameEngine::updateGame(float dt) {
    // Update players
    playerManager.updatePlayers(dt);
    
    // Update bullets
    bulletManager.updateBullets(dt);
    
    // Process player firing
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Player 0 shoots toward mouse position
        Vector2 mousePos = GetMousePosition();
        Vector2 player0Pos = playerManager.getPlayerPosition(0);
        bulletManager.addBullet(player0Pos, mousePos,0);
    }
    
    // AI or second player firing (simplified)
    static float aiFireTimer = 0.0f;
    aiFireTimer += dt;
    if (playerManager.isPlayerAlive(1) && aiFireTimer >= 1.0f) {  // Fire every second
        Vector2 player1Pos = playerManager.getPlayerPosition(1);
        Vector2 player0Pos = playerManager.getPlayerPosition(0);
        bulletManager.addBullet(player1Pos, player0Pos,1);  // AI targets player 0
        aiFireTimer = 0.0f;
    }
    
    // Check for collisions
    checkCollisions();
}


void GameEngine::renderGame() {
    // Game rendering  
    // Display health for players
    DrawText(TextFormat("Player 1 Health: %.0f", playerManager.getPlayerHealth(0)), 10, 40, 20, DARKGREEN);
    DrawText(TextFormat("Player 2 Health: %.0f", playerManager.getPlayerHealth(1)), 10, 70, 20, DARKBLUE);
}


void GameEngine::checkCollisions(){
        // Get bullet positions and check against player positions
    const std::vector<Bullet>& bullets = bulletManager.getBullets();
    
    for (size_t i = 0; i < bullets.size(); i++) {
        const Bullet& bullet = bullets[i];
        
        // Check collisions with players
        for (int playerID = 0; playerID < 2; playerID++) {
            Vector2 playerPos = playerManager.getPlayerPosition(playerID);
            float playerSize = 20.0f;  // Player size from drawPlayer
            
            // Simple collision check (circle vs rectangle)
            if (CheckCollisionCircleRec(
                    bullet.position, 
                    5.0f,  // Bullet radius
                    {playerPos.x, playerPos.y, playerSize, playerSize})) {
                
                // Don't damage player if it's their own bullet
                if (bullet.ownerID != playerID) {
                    playerManager.damagePlayer(playerID, 10.0f);
                    bulletManager.removeBullet(i);
                    break;
                }
            }
        }
    }

}