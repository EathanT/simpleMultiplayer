#ifndef GAME_H
#define GAME_H

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "player.h"
#include "bullet.h"


class GameEngine{
    public:
        GameEngine(){
        	playerManager.addPlayer(0, DEFAULT_POSITION, DEFAULT_HEALTH, DEFAULT_SPEED);
    
            // Add a second player for multiplayer
            Vector2 player2Pos = {GetScreenWidth()/2.0f + 100, GetScreenHeight()/2.0f + 100};
            playerManager.addPlayer(1, player2Pos, DEFAULT_HEALTH, DEFAULT_SPEED);

        }
        ~GameEngine() = default; 
        

        void updateGame(float dt);

        void renderGame();
    private:
	    BulletManager bulletManager; // Bullet Logic 
	    PlayerManager playerManager; // Player Logic

        void checkCollisions();
};

#endif