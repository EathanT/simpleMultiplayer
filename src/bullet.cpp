#include "bullet.h"

void BulletManager::drawBullet(Vector2 position, float radius, Color color){
	DrawCircle(position.x, position.y, radius, color);
}



//Add new bullet
void BulletManager::addBullet(Vector2 startPos, Vector2 targetPos){	

	//Getting the initial direction from start to target
	Vector2 dir{
		(targetPos.x - startPos.x),
		(targetPos.y - startPos.y)
	};

	//Normalize direction vector
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0.0f){
		dir.x /= length;
		dir.y /= length;
	}

	//Make the bullet
	Bullet newBullet;
	newBullet.position = startPos;
	newBullet.velocity = dir;
	newBullet.distanceTraveled = 0.0f;
	
	//Add to bullets vector
	bullets.push_back(newBullet);	

}


//Update Bullet each frame
void BulletManager::updateBullets(float deltaTime){	
	//iterate over all bullets
    for(size_t i = 0; i < bullets.size();){
		Bullet& b = bullets[i];


		// Move the bullet based of velocity * speed * deltaTime
		Vector2 movement{
			b.velocity.x * 300.0f * deltaTime,
			b.velocity.y * 300.0f * deltaTime
		};	

		// Update the bullet's pos and far its traveld
		b.position.x += movement.x;
		b.position.y += movement.y;
		
		//Increase traveled dis by magnitude of movement
		b.distanceTraveled += sqrt(movement.x * movement.x + movement.y * movement.y);

		// Check if bullet went passed its max dis
		if(b.distanceTraveled >= 600.0f){
			// Remove bullet
			bullets.erase(bullets.begin() + i);	
		} else {
			// Only increment i if not erased
			i++;
		}	

    	// Draw updated bullet
    	drawBullet(b.position, 5.0f, BLACK);
		
	}

}


//Get how far bullet has traveled
float BulletManager::getDistanceTraveled(size_t index) const{
	if(index < bullets.size()){
		return bullets[index].distanceTraveled;	
	}

	return 0.0f;
}


