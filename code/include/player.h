#ifndef PLAYER_H
#define PLAYER_H

#include <QPointF>
#include <QSizeF>

class Player
{
public:
    Player();

    // Getters
    QPointF getPosition() const;
    QSizeF getSize() const;
    qreal getAngle() const;
    int getHealth() const;

    // Setters / actions
    void setAngle(qreal angle);
    void setPosition(const QPointF& pos);
    void setHealth(int value);
    void takeDamage(int amount);
    void heal(float percent);

    float getDamageCooldown() const { return damageCooldown; }
    void setDamageCooldown(float value) { damageCooldown = value; }

private:
    QPointF position;
    QSizeF size;
    qreal angle;  // direction player is facing
    int health;
    int maxHealth;

    float damageCooldown;
};

#endif // PLAYER_H