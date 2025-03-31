#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

//bullets
struct Bullet{
	Vector2 position; // Position of bullet
	Vector2 velocity;  // Velocity vector( direction * speed)
	float distanceTraveled; // How far its gone
};

// bullet projectile
class BulletManager{

	private:
	    //current bullets on screen
	    vector<Bullet> bullets; 
		
		// Helper method to draw a single bullet	
		void drawBullet(Vector2 position, float radius, Color color);
	public:
		BulletManager() = default;
		~BulletManager() = default;
		
		// Add new bullet with start and end
		void addBullet(Vector2 startPos, Vector2 targetPos);

		// Update all bullets(movement, removal, etc)
		// deltaTime is time in seconds since last frame
		void updateBullets(float deltaTime);

		// get Distance
		float getDistanceTraveled(size_t index) const;
};

#endif
