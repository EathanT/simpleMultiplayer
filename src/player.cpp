#include "player.h"

PlayerManager::~PlayerManager() {
    // Free allocated memory pointers
    for (Player* player : players) {
        delete player;
    }
    players.clear();
}

// Add player to game/screen (players vector)
void PlayerManager::addPlayer(int playerID, Vector2 position, float health, float speed) {
    // Set player color based on ID
    Color playerColor = (playerID == 0) ? DARKGREEN : DARKBLUE;

    // Push back values of datatype Player to the players vector
    Player* newPlayer = new Player{
        playerID,
        position,
        health,
        speed,
        playerColor
    };

    players.push_back(newPlayer);
}

// Update players with delta time and input
void PlayerManager::updatePlayers(float dt) {
    deltaTime = dt;

    // Go through all players in player vector and update each 
    for (Player* player : players) {
        if (player->health > 0) {
            // Handle player input based on ID
            if (player->ID == 0) {
                handlePlayer1Input(player);
            } else {
                handlePlayer2Input(player);
            }
            
            // Keep player within screen bounds
            keepInBounds(player);
            
            // Draw player
            drawPlayer(player);
        }
    }
}

// Draw the player on the screen
void PlayerManager::drawPlayer(Player* p1) {
    // Draw player body
    DrawRectangleV(p1->position, {20.0f, 20.0f}, p1->color);
    
    // Draw health bar above player
    float healthBarWidth = 30.0f;
    float healthBarHeight = 5.0f;
    float healthPercent = p1->health / DEFAULT_HEALTH;
    
    // Health bar background
    DrawRectangle(
        p1->position.x - 5,
        p1->position.y - 15,
        healthBarWidth,
        healthBarHeight,
        GRAY
    );
    
    // Health bar fill
    DrawRectangle(
        p1->position.x - 5,
        p1->position.y - 15,
        healthBarWidth * healthPercent,
        healthBarHeight,
        (healthPercent > 0.5f) ? GREEN : RED
    );
    
    // Draw player ID
    DrawText(
        TextFormat("%d", p1->ID),
        p1->position.x + 7,
        p1->position.y + 2,
        16,
        WHITE
    );
}

// Controls for player 1 (WASD)
void PlayerManager::handlePlayer1Input(Player* p1) {
    float speed = p1->speed * deltaTime;

    // Player Movement
    if (IsKeyDown(KEY_D))
        p1->position.x += speed;
    if (IsKeyDown(KEY_A))
        p1->position.x -= speed;
    if (IsKeyDown(KEY_W))
        p1->position.y -= speed;
    if (IsKeyDown(KEY_S))
        p1->position.y += speed;
}

// Controls for player 2 (arrow keys or simple AI)
void PlayerManager::handlePlayer2Input(Player* p2) {
    float speed = p2->speed * deltaTime;
    
    // Simple AI - follow player 1 at a distance
    if (players.size() > 1 && players[0]->health > 0) {
        Vector2 player1Pos = players[0]->position;
        Vector2 direction = {
            player1Pos.x - p2->position.x,
            player1Pos.y - p2->position.y
        };
        
        // Calculate distance to player 1
        float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
        
        // Only move if player is far enough
        if (distance > 150.0f) {
            // Normalize and apply speed
            if (distance > 0) {
                direction.x = direction.x / distance * speed;
                direction.y = direction.y / distance * speed;
                
                p2->position.x += direction.x;
                p2->position.y += direction.y;
            }
        }
    }
    
    // Use arrow keys for manual control
    // if (IsKeyDown(KEY_RIGHT)) p2->position.x += speed;
    // if (IsKeyDown(KEY_LEFT)) p2->position.x -= speed;
    // if (IsKeyDown(KEY_UP)) p2->position.y -= speed;
    // if (IsKeyDown(KEY_DOWN)) p2->position.y += speed;
}

// Keep players within screen bounds
void PlayerManager::keepInBounds(Player* player) {
    float playerSize = 20.0f;
    
    // Screen boundaries
    if (player->position.x < 0) player->position.x = 0;
    if (player->position.y < 0) player->position.y = 0;
    if (player->position.x > GetScreenWidth() - playerSize)
        player->position.x = GetScreenWidth() - playerSize;
    if (player->position.y > GetScreenHeight() - playerSize)
        player->position.y = GetScreenHeight() - playerSize;
}

// Get player position by ID
Vector2 PlayerManager::getPlayerPosition(int playerID) {
    for (Player* player : players) {
        if (player->ID == playerID) {
            return player->position;
        }
    }
    return {0, 0}; // Default pos
}

// Get player health by ID
float PlayerManager::getPlayerHealth(int playerID) {
    for (Player* player : players) {
        if (player->ID == playerID) {
            return player->health;
        }
    }
    return 0.0f; // Default
}

// Damage player by ID
void PlayerManager::damagePlayer(int playerID, float damage) {
    for (Player* player : players) {
        if (player->ID == playerID) {
            player->health = std::max(0.0f, player->health - damage);
            break;
        }
    }
}

// Check if player is alive
bool PlayerManager::isPlayerAlive(int playerID) {
    for (Player* player : players) {
        if (player->ID == playerID) {
            return player->health > 0;
        }
    }
    return false;
}