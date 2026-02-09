#include "collisionmanager.h"
#include <QDebug>

// This function checks if any bullets hit any zombies.
// If a bullet hits a zombie, the zombie is removed and player gets points.
// Level 2+ bullets can pierce through multiple zombies.
void CollisionManager::checkBulletZombieCollisions(
    std::vector<std::unique_ptr<Bullet>>& bullets,  // list of bullets
    std::vector<std::unique_ptr<Zombie>>& zombies,  // list of zombies
    ScoreBoard& scoreboard)                         // keeps track of the score
{
    // Go through every bullet one by one
    for (auto bIt = bullets.begin(); bIt != bullets.end(); )
    {
        bool bulletDead = false;  // bullet dies when pierce count reaches 0
        QPointF bPos = (*bIt)->getPosition(); // get bullet position

        // Go through every zombie for this bullet
        for (auto zIt = zombies.begin(); zIt != zombies.end(); )
        {
            QPointF zPos = (*zIt)->getPosition(); // get zombie position

            // Work out how far the bullet is from the zombie (distance)
            float dx = bPos.x() - zPos.x();
            float dy = bPos.y() - zPos.y();
            float distSq = dx * dx + dy * dy; // distance squared (no need for sqrt)

            // If distance is less than 30 pixels, it's a hit!
            if (distSq < 30 * 30)
            {
                scoreboard.incrementScore(10); // add 10 points for a zombie hit
                scoreboard.addKill();
                zIt = zombies.erase(zIt); // remove the zombie from the list
                
                // Decrease bullet's pierce count
                (*bIt)->decrementPierce();
                
                // If bullet can't pierce anymore, mark it for removal
                if (!(*bIt)->canPierce()) {
                    bulletDead = true;
                    break;  // stop checking more zombies for this bullet
                }
            }
            else
                ++zIt; // move to the next zombie
        }

        // If the bullet is dead (pierce count = 0), remove it
        if (bulletDead)
            bIt = bullets.erase(bIt);
        else
            ++bIt; // otherwise, move to the next bullet
    }
}