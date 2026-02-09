#ifndef POWERUP_H
#define POWERUP_H

#include <QPointF>
#include <QPixmap>
#include <QString>

enum class PowerUpType {
    Heal,
    Shield,
    PowerUp
};

class PowerUp
{
public:
    PowerUp(const QPointF& pos, PowerUpType type);

    QPointF getPosition() const { return position; }
    PowerUpType getType() const { return type; }
    const QPixmap& getSprite() const { return sprite; }
    bool isAlive() const { return alive; }
    void setAlive(bool value) { alive = value; }
    
    // Check if point is within powerup bounds (for clicking)
    bool contains(const QPointF& point) const;
    
    QString getTypeName() const;

private:
    QPointF position;
    PowerUpType type;
    QPixmap sprite;
    bool alive;
    static const int SIZE = 50;  // PowerUp click detection size
};

#endif // POWERUP_H
