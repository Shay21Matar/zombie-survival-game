#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <memory>
#include "bullet.h"
#include "zombie.h"
#include "scoreboard.h"

class CollisionManager
{
public:
    static void checkBulletZombieCollisions(
        std::vector<std::unique_ptr<Bullet>>& bullets,
        std::vector<std::unique_ptr<Zombie>>& zombies,
        ScoreBoard& scoreboard);
};

#endif // COLLISIONMANAGER_H