#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QPointF>
#include <QSizeF>
#include <QPixmap>
#include <QDateTime>

enum class ZombieType {
    Normal,
    Tank,
    Ninja
};

class Zombie
{
public:
    Zombie(const QPointF& startPos, float speed = 40.0f, ZombieType type = ZombieType::Normal);

    void update(float dt, const QPointF& playerPos);
    QPointF getPosition() const;

    bool isAlive() const { return alive; }
    void setAlive(bool value) { alive = value; }
    
    ZombieType getType() const { return zombieType; }

    // ---- NEW GETTERS FOR SPRITE ANIMATION ----
    const QPixmap& getSpriteSheet() const { return spriteSheet; }
    const QPixmap& getCurrentSprite() const;  // For animated tank zombies
    int getCurrentFrame() const { return currentFrame; }
    int getFrameWidth() const { return frameWidth; }
    int getFrameHeight() const { return frameHeight; }

private:
    QPointF position;
    float speed;
    bool alive = true;
    ZombieType zombieType;

    // ---- NEW ANIMATION FIELDS ----
    QPixmap spriteSheet;
    QPixmap tankFrame1;  // Tank zombie animation frames
    QPixmap tankFrame2;
    QPixmap tankFrame3;
    QPixmap normalFrame1;  // Normal zombie animation frames
    QPixmap normalFrame2;
    QPixmap normalFrame3;
    QPixmap normalFrame4;
    QPixmap ninjaFrame1;  // Ninja zombie animation frames
    QPixmap ninjaFrame2;
    QPixmap ninjaFrame3;
    int currentFrame = 0;

    // 2 columns, 4 rows (7 actual frames)
    const int frameWidth = 320;   // 640 / 2
    const int frameHeight = 180;  // 720 / 4

    qint64 lastFrameTime = 0;

    void advanceAnimation();
};

#endif // ZOMBIE_H