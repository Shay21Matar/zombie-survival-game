#include "bullet.h"
#include <QDebug>

// This class controls how each bullet moves and lives in the game.

// Constructor: sets where the bullet starts, how fast it moves, and how long it lasts
Bullet::Bullet(const QPointF& startPos, const QPointF& vel, float lifeSpan)
    : position(startPos), velocity(vel), lifeRemaining(lifeSpan), pierceCount(1)
{
    sprite.load(":/images/bullet1.png");  // load bullet1.png
    if (sprite.isNull()) {
        sprite.load("images/bullet1.png");  // Try file system
    }
    
    // Don't scale here - we'll scale when drawing
}

// This function updates the bullet's position and lifetime each frame
void Bullet::update(float dt)
{
    // Move the bullet by its velocity (speed and direction)
    // dt is the time passed since the last frame
    position += velocity * dt;

    // Decrease how much lifetime the bullet has left
    lifeRemaining -= dt;
    
    // Track spawn time for visibility
    spawnTime += dt;
}

// Returns the bullet’s current position
QPointF Bullet::getPosition() const
{
    return position;
}

// Checks if the bullet is still active (alive)
// Returns true if the bullet hasn’t expired and is still on the screen
bool Bullet::isAlive() const
{
    return lifeRemaining > 0 &&            // still has time left
           position.x() >= 0 && position.x() <= 751 &&   // inside screen width
           position.y() >= 0 && position.y() <= 391;     // inside screen height
}

void Bullet::setSprite(const QString& path)
{
    sprite.load(path);
    if (sprite.isNull()) {
        // Try without resource prefix
        QString plainPath = path;
        plainPath.replace(":/images/", "images/");
        sprite.load(plainPath);
    }
    // Don't scale here - scaling happens when drawing
}