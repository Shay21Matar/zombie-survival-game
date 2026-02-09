#include "entityfactory.h"
#include <QtMath>
#include <QRandomGenerator>   // for random zombie spawn positions

// This class
std::unique_ptr<Bullet> EntityFactory::createBullet(const QPointF& startPos, qreal angle, float speed, int pierceCount)
{
    // Convert angle from degrees to radians
    float rad = qDegreesToRadians(angle);

    // Calculate bullet's velocity (direction × speed)
    QPointF velocity(qCos(rad) * speed, qSin(rad) * speed);

    // Create and return a new bullet using smart pointer
    auto bullet = std::make_unique<Bullet>(startPos, velocity);
    bullet->setPierceCount(pierceCount);
    
    // Level 2+ bullets use bullet2.png
    if (pierceCount > 1) {
        bullet->setSprite(":/images/bullet2.png");
    }
    
    return bullet;
}

// ------------------ ZOMBIE FACTORY ------------------
std::unique_ptr<Zombie> EntityFactory::createZombie(int level)
{
    // Pick a random side of the screen (0=top, 1=right, 2=bottom, 3=left)
    int side = QRandomGenerator::global()->bounded(4);
    QPointF pos;

    // Use actual game area size (751x391)
    int screenWidth = 751;
    int screenHeight = 391;
    int margin = 20;  // How far off-screen to spawn

    // Set zombie's start position depending on side
    switch (side)
    {
    case 0: pos = QPointF(QRandomGenerator::global()->bounded(0, screenWidth), -margin); break;  // top
    case 1: pos = QPointF(screenWidth + margin, QRandomGenerator::global()->bounded(0, screenHeight)); break;  // right
    case 2: pos = QPointF(QRandomGenerator::global()->bounded(0, screenWidth), screenHeight + margin); break;  // bottom
    case 3: pos = QPointF(-margin, QRandomGenerator::global()->bounded(0, screenHeight)); break;  // left
    }
    
    // Level 3+: Mix of all three types
    if (level >= 3) {
        int type = QRandomGenerator::global()->bounded(3);
        if (type == 0) {
            return std::make_unique<Zombie>(pos, 40.0f, ZombieType::Normal);
        } else if (type == 1) {
            return std::make_unique<Zombie>(pos, 20.0f, ZombieType::Tank);  // Slower
        } else {
            return std::make_unique<Zombie>(pos, 80.0f, ZombieType::Ninja);  // Faster!
        }
    }
    
    // Level 2: 50% normal, 50% tank
    if (level >= 2 && QRandomGenerator::global()->bounded(2) == 0) {
        return std::make_unique<Zombie>(pos, 20.0f, ZombieType::Tank);
    }

    // Level 1: Only normal zombies
    return std::make_unique<Zombie>(pos, 40.0f, ZombieType::Normal);
}