#include "bullet.h"

void BulletManager::drawBullet(const Bullet& bull) const{
	switch(bull.type){
		case BulletType::Normal: {	
			DrawCircle(bull.position.x, bull.position.y, bull.radius, BLACK);
			break;
		}
		case BulletType::Laser:{	
			DrawCircle(bull.position.x, bull.position.y, bull.radius, RED);
			break;	
		}
		case BulletType::Explosive:{	
			DrawCircle(bull.position.x, bull.position.y, bull.radius, ORANGE);
			break;
		}
		default:{ // Normal Bullet
			DrawCircle(bull.position.x, bull.position.y, bull.radius, BLACK);
			break;
		}
	}
}



//Add new bullet
void BulletManager::addBullet(Vector2 startPos, Vector2 targetPos, float speed, float radius, float maxDistance, BulletType bulletType){	

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
	newBullet.speed = speed;
	newBullet.distanceTraveled = 0.0f;
	newBullet.maxDistance = maxDistance;
	newBullet.radius = radius;
	newBullet.type = bulletType; 
	
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
			b.velocity.x * b.speed * deltaTime,
			b.velocity.y * b.speed * deltaTime
		};	

		// Update the bullet's pos and far its traveld
		b.position.x += movement.x;
		b.position.y += movement.y;
		//Increase traveled dis by magnitude of movement
		b.distanceTraveled += sqrt(movement.x * movement.x + movement.y * movement.y);

		// Check if bullet went passed its max dis
		if(b.distanceTraveled >= b.maxDistance){
			// Remove bullet
			bullets.erase(bullets.begin() + i);	
		} else {
			// Only increment i if not erased
			i++;
		}	

		
	}
}

// Draw all bullets
void BulletManager::drawBullets() const{
	for(const Bullet& b : bullets){
		drawBullet(b);
	}
}

//Get how far bullet has traveled
float BulletManager::getDistanceTraveled(size_t index) const{
	if(index < bullets.size()){
		return bullets[index].distanceTraveled;	
	}

	return 0.0f;
}


