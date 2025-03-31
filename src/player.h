#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"

#define DEFAULT_ID 0 // Default ID (first player)
#define DEFAULT_POSITION {GetScreenWidth()/2.0f,GetScreenHeight()/2.0f} //Default Player Position is middle of the screen
#define DEFAULT_HEALTH 100.0f // Default player health is 100
#define DEFAULT_SPEED 250.0f // Default player speed is 250 pixels a second

struct Player{
    int ID; // ID of player
    Vector2 position; // Position of the player
    float health;  // Health of the player 
    float speed; // Speed of the player
};

class PlayerManager{
    public: 
	    PlayerManager() = default;
        ~PlayerManager();

        void addPlayer(int playerID, Vector2 position, float health, float speed); // Add player to game (player vector)
    	void updatePlayers(float dt);  // Update all players with delta time
        Vector2 getPlayerPosition(int playerID); // get Vector2 of player by ID

    private:
	    vector<Player*> players; // Vector of playersa
        float deltaTime; // Current Delta time

        void drawPlayer(Player* p1); // draw the player on the screen
        void movePlayer(Player* p1); // move the player
        
};

#endif
