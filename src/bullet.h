#ifndef BULLET_H
#define BULLET_H

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "raylib.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

//Bullet types
enum class BulletType: int {
	Normal,
	Laser,
	Explosive,
	// Add more here
};

//bullets
struct Bullet{
	Vector2 position; //Current position
	Vector2 velocity;  // Velocity vector( direction * speed)
	float speed; // Base movement speed
	float distanceTraveled; // How far its gone
	float maxDistance; // Max travel Dist
	float radius; // Bullet size	

	BulletType type; 
};

// bullet projectile
class BulletManager{

	private:
		vector<Bullet> bullets; //current bullets on screen
		// Helper meth to draw a single bullet	
		void drawBullet(const Bullet& bull) const;
	public:
		BulletManager() = default;
		~BulletManager() = default;
		
		// Add new bullet with start and end
		void addBullet(Vector2 startPos, Vector2 targetPos, float speed, float radius, float maxDistance, BulletType bulletType);

		// Update all bullets(movement, removal, etc)
		// deltaTime is time in seconds since last frame
		void updateBullets(float deltaTime);

		//draw all bullets
		void drawBullets() const;
		// get Distance
		float getDistanceTraveled(size_t index) const;
};

#endif
