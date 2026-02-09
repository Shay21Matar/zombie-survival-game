#ifndef BULLET_H
#define BULLET_H

#include <QPointF>
#include <QSizeF>
#include <QPixmap>

class Bullet
{
public:
    Bullet(const QPointF& startPos, const QPointF& vel, float lifeSpan = 3.0f);

    void update(float dt);
    QPointF getPosition() const;
    bool isAlive() const;
    bool isVisible() const { return spawnTime >= 0.1f; }  // Visible after 0.1 seconds
    
    int getPierceCount() const { return pierceCount; }
    void decrementPierce() { pierceCount--; }
    bool canPierce() const { return pierceCount > 0; }

    // --- New for sprite ---
    void setSprite(const QString& path);
    const QPixmap& getSprite() const { return sprite; }
    
    void setPierceCount(int count) { pierceCount = count; }

    // --- New for speed scaling ---
    void scaleVelocity(float factor) { velocity *= factor; }

private:
    QPointF position;
    QPointF velocity;
    float lifeRemaining;
    float spawnTime = 0.0f;  // Time since spawn
    QPixmap sprite;   // bullet image
    int pierceCount;  // how many zombies it can hit (1 = normal, 3+ = level 2)
};

#endif // BULLET_H