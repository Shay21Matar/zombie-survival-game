#pragma once
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <vector>
#include <memory>
#include "player.h"
#include "zombie.h"
#include "bullet.h"
#include "scoreboard.h"
#include "powerup.h"

class GameController : public QObject{
    Q_OBJECT
public:
    GameController(QObject *parent = nullptr);

    void startLevel(int level);
    void startInfinityMode();  // Start infinity mode
    void update();        // called every frame
    void draw(QPainter &p);
    void setMousePosition(const QPointF &pos);
    void fireBullet();    // shoot a bullet
    void resetGame();     // reset game state
    bool isGameOver() const;  // check if player is dead
    bool shouldLevelUp() const;  // check if player reached kill goal
    void advanceToLevel2();  // setup level 2
    void advanceToLevel3();  // setup level 3
    void handleClick(const QPointF& clickPos);  // handle mouse clicks for powerups

    int getKills() const;
    int getKillGoal() const;
    int getScore() const;
    int getLevel() const { return level; }
    bool isInfinityMode() const { return infinityMode; }

signals:
    void killCountChanged(int current, int goal);
    void scoreChanged(int score);
    void healthChanged(int health);

private:
    void activatePowerUp(PowerUpType type);  // Activate a powerup effect
    
    int level;
    int kills;
    int killGoal;
    bool infinityMode;  // Track if in infinity mode
    Player player;
    ScoreBoard scoreboard;
    
    // Game entities
    std::vector<std::unique_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<PowerUp>> powerups;
    
    // PowerUp slots (max 2)
    std::vector<PowerUpType> powerupSlots;
    
    // Active boost effects
    bool shieldActive;
    float shieldTimer;
    bool powerUpActive;
    float powerUpTimer;
    QString activeBoostName;
    float activeBoostTimer;
    
    // Spawn timing
    float zombieSpawnTimer;
    float zombieSpawnInterval;
    float bulletFireTimer;
    float bulletFireInterval;
    float powerupSpawnTimer;
    float powerupSpawnInterval;
    
    // Sprites
    QPixmap backgroundSprite;
    QPixmap playerBodySprite;
    QPixmap playerHeadSprite;
    
    // Mouse tracking
    QPointF mousePosition;
};
