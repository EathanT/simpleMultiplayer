#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include <vector>
#include <cmath>
#include <iostream>

// Bullet configuration
#define BULLET_SPEED 500.0f
#define BULLET_RADIUS 5.0f
#define BULLET_MAX_DISTANCE 800.0f

// Bullets
struct Bullet {
    Vector2 position;       // Position of bullet
    Vector2 velocity;       // Velocity vector (direction * speed)
    float distanceTraveled; // How far it's gone
    int ownerID;           // ID of player who fired bullet
    Color color;           // Bullet color
};

// Bullet projectile manager
class BulletManager {
private:
    // Current bullets on screen
    std::vector<Bullet> bullets;
    
    // Helper method to draw a single bullet    
    void drawBullet(const Bullet& bullet);
    
public:
    BulletManager() = default;
    ~BulletManager() = default;
    
    // Add new bullet with start and end position, and owner ID
    void addBullet(Vector2 startPos, Vector2 targetPos, int ownerID = 0);
    
    // Update all bullets
    // deltaTime is time in seconds since last frame
    void updateBullets(float deltaTime);
    
    // Remove a bullet by index
    void removeBullet(size_t index);
    
    // Get distance traveled
    float getDistanceTraveled(size_t index) const;
    
    // Get all bullets for collision detection
    const std::vector<Bullet>& getBullets() const { return bullets; }
};

#endif