#include "player.h"

PlayerManager::~PlayerManager(){
	// free allocated memory pointers
	for(Player* player : players){
		delete player;
	}
	players.clear();
}

// Add player to game/screen (players vector)
void PlayerManager::addPlayer(int playerID, Vector2 position, float health, float speed){

	// Push back values of datatype Player to the players vector
	Player* newPlayer = new Player{
		playerID,
		position,
		health,
		speed
	};

	players.push_back(newPlayer);
}


// Update players with delta time and input
void PlayerManager::updatePlayers(float dt){
	deltaTime = dt;

	// Go through all players in player vector and update each 
	for(Player* player : players){
		movePlayer(player);
		drawPlayer(player);

	}

}



// Draw the player on the screen
void PlayerManager::drawPlayer(Player* p1){
	DrawRectangleV(p1->position, {20.0f, 20.0f}, BLACK);

}

// Move the players position based on input
void PlayerManager::movePlayer(Player* p1){
	float speed = p1->speed * deltaTime;

	// Player Movement	
	if(IsKeyDown(KEY_D))
		p1->position.x += speed; 
	if(IsKeyDown(KEY_A))
		p1->position.x -= speed;	
	if(IsKeyDown(KEY_W))
		p1->position.y -= speed;	
	if(IsKeyDown(KEY_S))
		p1->position.y += speed;	

}

// Get player pos by IDEFAULT_POSITION, DEFAULT_HEALTH, DEFAULT_SPEED);
Vector2 PlayerManager::getPlayerPosition(int playerID) {
	if(playerID >= 0 && playerID < players.size()){
		return players[playerID]->position;
	}

	return {0, 0}; // Default pos
}
