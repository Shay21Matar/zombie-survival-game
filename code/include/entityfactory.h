#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QPointF>
#include <memory>
#include "bullet.h"
#include "zombie.h"


class EntityFactory
{
public:
    static std::unique_ptr<Bullet> createBullet(const QPointF& startPos, qreal angle, float speed = 400.0f, int pierceCount = 1);
    static std::unique_ptr<Zombie> createZombie(int level = 1);
};

#endif // ENTITYFACTORY_H