#include "bullet.h"

// Draw bullet
void BulletManager::drawBullet(const Bullet& bullet) {
    DrawCircleV(bullet.position, BULLET_RADIUS, bullet.color);
    
    // Trail effect
    for (int i = 1; i <= 3; i++) {
        Vector2 trailPos = {
            bullet.position.x - bullet.velocity.x * i * 3.0f,
            bullet.position.y - bullet.velocity.y * i * 3.0f
        };
        
        Color trailColor = bullet.color;
        trailColor.a = 120 - i * 30;  // Fade out
        
        DrawCircleV(trailPos, BULLET_RADIUS - i, trailColor);
    }
}

// Add new bullet
void BulletManager::addBullet(Vector2 startPos, Vector2 targetPos, int ownerID) {    
    // Getting the initial direction from start to target
    Vector2 dir{
        (targetPos.x - startPos.x),
        (targetPos.y - startPos.y)
    };

    // Normalize direction vector
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0.0f) {
        dir.x /= length;
        dir.y /= length;
    }

    // Set bullet color based on owner
    Color bulletColor = (ownerID == 0) ? GREEN : BLUE;

    // Make the bullet
    Bullet newBullet;
    newBullet.position = startPos;
    newBullet.velocity = dir;
    newBullet.distanceTraveled = 0.0f;
    newBullet.ownerID = ownerID;
    newBullet.color = bulletColor;
    
    // Add to bullets vector
    bullets.push_back(newBullet);
}

// Update Bullet each frame
void BulletManager::updateBullets(float deltaTime) {    
    // Iterate over all bullets
    for (size_t i = 0; i < bullets.size();) {
        Bullet& b = bullets[i];

        // Move the bullet based on velocity * speed * deltaTime
        Vector2 movement{
            b.velocity.x * BULLET_SPEED * deltaTime,
            b.velocity.y * BULLET_SPEED * deltaTime
        };    

        // Update the bullet's position and how far it's traveled
        b.position.x += movement.x;
        b.position.y += movement.y;
        
        // Increase traveled distance by magnitude of movement
        b.distanceTraveled += sqrt(movement.x * movement.x + movement.y * movement.y);

        // Check if bullet went past its max distance or out of screen
        if (b.distanceTraveled >= BULLET_MAX_DISTANCE || 
            b.position.x < 0 || b.position.x > GetScreenWidth() ||
            b.position.y < 0 || b.position.y > GetScreenHeight()) {
            // Remove bullet
            bullets.erase(bullets.begin() + i);    
        } else {
            // Draw updated bullet
            drawBullet(b);
            // Only increment i if not erased
            i++;
        }    
    }
}

// Remove a bullet by index
void BulletManager::removeBullet(size_t index) {
    if (index < bullets.size()) {
        bullets.erase(bullets.begin() + index);
    }
}

// Get how far bullet has traveled
float BulletManager::getDistanceTraveled(size_t index) const {
    if (index < bullets.size()) {
        return bullets[index].distanceTraveled;    
    }
    return 0.0f;
}
