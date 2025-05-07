#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"

#define DEFAULT_ID 0  // Default ID (first player)
#define DEFAULT_POSITION {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}  // Default Player Position
#define DEFAULT_HEALTH 100.0f  // Default player health
#define DEFAULT_SPEED 250.0f  // Default player speed

struct Player {
    int ID;  // ID of player
    Vector2 position;  // Position of the player
    float health;  // Health of the player 
    float speed;  // Speed of the player
    Color color;  // Player color
};

class PlayerManager {
public: 
    PlayerManager() = default;
    ~PlayerManager();

    // Add player to game (player vector)
    void addPlayer(int playerID, Vector2 position, float health, float speed);
    
    // Update all players with delta time
    void updatePlayers(float dt);
    
    // Get Vector2 of player by ID
    Vector2 getPlayerPosition(int playerID);
    
    // Get player health by ID
    float getPlayerHealth(int playerID);
    
    // Damage player by ID
    void damagePlayer(int playerID, float damage);
    
    // Check if player is alive
    bool isPlayerAlive(int playerID);

private:
    std::vector<Player*> players;  // Vector of players
    float deltaTime;  // Current Delta time

    // Draw the player on the screen
    void drawPlayer(Player* p1);
    
    // Move the player
    void movePlayer(Player* p1);
    
    // Controls for player 1 (keyboard)
    void handlePlayer1Input(Player* p1);
    
    // Controls for player 2 (AI or different keys)
    void handlePlayer2Input(Player* p2);
    
    // Keep players within screen bounds
    void keepInBounds(Player* player);
};

#endif