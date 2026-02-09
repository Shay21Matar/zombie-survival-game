#include "gamecontroller.h"
#include "entityfactory.h"
#include "collisionmanager.h"
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>

GameController::GameController(QObject *parent)
    : QObject(parent), level(0), kills(0), killGoal(0), infinityMode(false), mousePosition(0, 0),
      zombieSpawnTimer(0), zombieSpawnInterval(1.0f),  // Spawn zombie every 1 second
      bulletFireTimer(0), bulletFireInterval(0.5f),     // Fire bullet every 0.5 seconds
      powerupSpawnTimer(0), powerupSpawnInterval(10.0f),  // Spawn powerup every 10 seconds
      shieldActive(false), shieldTimer(0), powerUpActive(false), powerUpTimer(0),
      activeBoostTimer(0)
{
    // Try loading sprites from resources first
    backgroundSprite = QPixmap(":/images/background.png");
    playerBodySprite = QPixmap(":/images/playerbody.png");
    playerHeadSprite = QPixmap(":/images/gun1player.png");
    
    // If resources don't work, try loading from file system directly
    if (backgroundSprite.isNull()) {
        backgroundSprite = QPixmap("images/background.png");
    }
    if (playerBodySprite.isNull()) {
        playerBodySprite = QPixmap("images/playerbody.png");
    }
    if (playerHeadSprite.isNull()) {
        playerHeadSprite = QPixmap("images/gun1player.png");
    }
}

void GameController::startLevel(int levelNum)
{
    level = levelNum;
    kills = 0;
    
    // Level-based kill goals
    if (level == 1) killGoal = 30;
    else if (level == 2) killGoal = 60;
    else killGoal = 90;  // Level 3: need 90 kills to win
    
    // Reset player to center of screen and full health
    player.setPosition(QPointF(375.5, 195.5));  // Center of gameArea (751x391)
    player.setHealth(100);  // Reset health to 100
    player.setDamageCooldown(0);
    
    // Clear all zombies, bullets, and powerups
    zombies.clear();
    bullets.clear();
    powerups.clear();
    
    // Clear active powerup effects
    shieldActive = false;
    shieldTimer = 0;
    powerUpActive = false;
    powerUpTimer = 0;
    activeBoostTimer = 0;
    activeBoostName = "";
    
    // Reset scoreboard
    scoreboard.reset();
    scoreboard.setKillsToNextLevel(killGoal);
    
    // Reset spawn timer
    zombieSpawnTimer = 0;
    bulletFireTimer = 0;
    
    // Set spawn rate based on level
    if (level >= 3) {
        zombieSpawnInterval = 0.321f;  // Level 3: 3.11x faster (0.5 / 1.5 = 0.321)
    } else {
        zombieSpawnInterval = 0.67f;  // Level 1-2: 1.5x faster (every 0.67 seconds)
    }
    
    // Load sprites based on level
    if (level >= 3) {
        playerHeadSprite = QPixmap(":/images/gun3player.png");
        if (playerHeadSprite.isNull()) {
            playerHeadSprite = QPixmap("images/gun3player.png");
        }
    } else if (level >= 2) {
        playerHeadSprite = QPixmap(":/images/gun2player.png");
        if (playerHeadSprite.isNull()) {
            playerHeadSprite = QPixmap("images/gun2player.png");
        }
    } else {
        playerHeadSprite = QPixmap(":/images/gun1player.png");
        if (playerHeadSprite.isNull()) {
            playerHeadSprite = QPixmap("images/gun1player.png");
        }
    }
    
    emit killCountChanged(kills, killGoal);
    emit scoreChanged(scoreboard.getScore());
    emit healthChanged(player.getHealth());
}

void GameController::startInfinityMode()
{
    infinityMode = true;
    level = 3;  // Use level 3 as base
    kills = 0;
    killGoal = 9999;  // Effectively infinite
    
    // Reset player to center of screen and full health
    player.setPosition(QPointF(375.5, 195.5));
    player.setHealth(100);
    player.setDamageCooldown(0);
    
    // Clear all zombies, bullets, and powerups
    zombies.clear();
    bullets.clear();
    powerups.clear();
    
    // Clear active powerup effects
    shieldActive = false;
    shieldTimer = 0;
    powerUpActive = false;
    powerUpTimer = 0;
    activeBoostTimer = 0;
    activeBoostName = "";
    
    // Reset scoreboard
    scoreboard.reset();
    scoreboard.setKillsToNextLevel(killGoal);
    
    // Reset spawn timers
    zombieSpawnTimer = 0;
    bulletFireTimer = 0;
    
    // Infinity mode: same spawn rate as level 3
    zombieSpawnInterval = 0.321f;
    
    // Load level 3 gun sprite
    playerHeadSprite = QPixmap(":/images/gun3player.png");
    if (playerHeadSprite.isNull()) {
        playerHeadSprite = QPixmap("images/gun3player.png");
    }
    
    emit killCountChanged(kills, killGoal);
    emit scoreChanged(scoreboard.getScore());
    emit healthChanged(player.getHealth());
}

void GameController::update()
{
    // Update game logic each frame
    float dt = 0.016f;  // ~60 FPS
    
    // Update boost timers
    if (shieldActive) {
        shieldTimer -= dt;
        if (shieldTimer <= 0) {
            shieldActive = false;
        }
    }
    if (powerUpActive) {
        powerUpTimer -= dt;
        if (powerUpTimer <= 0) {
            powerUpActive = false;
        }
    }
    if (activeBoostTimer > 0) {
        activeBoostTimer -= dt;
    }
    
    // Update player damage cooldown
    float damageCooldown = player.getDamageCooldown();
    if (damageCooldown > 0) {
        player.setDamageCooldown(damageCooldown - dt);
    }
    
    // Zombie spawning
    zombieSpawnTimer += dt;
    if (zombieSpawnTimer >= zombieSpawnInterval) {
        zombies.push_back(EntityFactory::createZombie(level));  // Pass level to factory
        zombieSpawnTimer = 0;
    }
    
    // PowerUp spawning (every 10 seconds)
    powerupSpawnTimer += dt;
    if (powerupSpawnTimer >= powerupSpawnInterval) {
        // Random position within game area
        QPointF pos(QRandomGenerator::global()->bounded(50, 700),
                    QRandomGenerator::global()->bounded(50, 340));
        
        // Random type
        int typeRand = QRandomGenerator::global()->bounded(3);
        PowerUpType type = static_cast<PowerUpType>(typeRand);
        
        powerups.push_back(std::make_unique<PowerUp>(pos, type));
        powerupSpawnTimer = 0;
    }
    
    // Automatic bullet firing
    bulletFireTimer += dt;
    float currentFireInterval = powerUpActive ? bulletFireInterval * 0.5f : bulletFireInterval;
    if (bulletFireTimer >= currentFireInterval) {
        fireBullet();
        bulletFireTimer = 0;
    }
    
    // Update all zombies
    QPointF playerPos = player.getPosition();
    for (auto& zombie : zombies) {
        zombie->update(dt, playerPos);
    }
    
    // Update all bullets
    for (auto& bullet : bullets) {
        bullet->update(dt);
    }
    
    // Remove dead bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                      [](const std::unique_ptr<Bullet>& b) { return !b->isAlive(); }),
        bullets.end()
    );
    
    // Check bullet-zombie collisions
    int oldKills = scoreboard.getKills();
    CollisionManager::checkBulletZombieCollisions(bullets, zombies, scoreboard);
    
    // Update UI if kills changed
    if (scoreboard.getKills() != oldKills) {
        emit killCountChanged(scoreboard.getKills(), killGoal);
        emit scoreChanged(scoreboard.getScore());
    }
    
    // Check zombie-player collisions (unless shield is active)
    if (!shieldActive) {
        for (auto it = zombies.begin(); it != zombies.end(); ) {
            QPointF zombiePos = (*it)->getPosition();
            QPointF delta = playerPos - zombiePos;
            float distSq = delta.x() * delta.x() + delta.y() * delta.y();
            
            // If zombie touches player
            if (distSq < 40 * 40) {  // 40 pixel collision radius
                player.takeDamage(20);
                emit healthChanged(player.getHealth());
                it = zombies.erase(it);  // Remove zombie after hit
            } else {
                ++it;
            }
        }
    } else {
        // Shield is active, skip zombie collision iteration
        // (but still need to iterate for other logic if needed)
    }
}

void GameController::resetGame()
{
    // Reset everything to initial state
    kills = 0;
    level = 1;
    killGoal = 10;
    
    player.setPosition(QPointF(315, 120));
    player.setHealth(100);
    player.setDamageCooldown(0);
    
    zombies.clear();
    bullets.clear();
    
    scoreboard.reset();
    scoreboard.setKillsToNextLevel(killGoal);
    
    zombieSpawnTimer = 0;
    bulletFireTimer = 0;
    
    emit killCountChanged(kills, killGoal);
    emit scoreChanged(scoreboard.getScore());
    emit healthChanged(player.getHealth());
}

bool GameController::isGameOver() const
{
    return player.getHealth() <= 0;
}

bool GameController::shouldLevelUp() const
{
    // Check if reached kill goal and not on max level yet
    if (level == 1 && scoreboard.getKills() >= killGoal) return true;
    if (level == 2 && scoreboard.getKills() >= killGoal) return true;
    if (level == 3 && scoreboard.getKills() >= killGoal) return true;  // Win condition
    return false;
}

void GameController::advanceToLevel2()
{
    level = 2;
    killGoal = 60;  // Need 60 kills for level 2
    
    // Reset kills and score to 0 for new level
    scoreboard.resetKills();
    scoreboard.incrementScore(-scoreboard.getScore());  // Reset score to 0
    
    // Reset health to 100
    player.setHealth(100);
    
    // Clear entities
    zombies.clear();
    bullets.clear();
    powerups.clear();
    
    // Clear active powerup effects
    shieldActive = false;
    shieldTimer = 0;
    powerUpActive = false;
    powerUpTimer = 0;
    activeBoostTimer = 0;
    activeBoostName = "";
    
    // Update scoreboard
    scoreboard.setKillsToNextLevel(killGoal);
    
    // Reset spawn timers
    zombieSpawnTimer = 0;
    bulletFireTimer = 0;
    
    // Load level 2 gun sprite
    playerHeadSprite = QPixmap(":/images/gun2player.png");
    if (playerHeadSprite.isNull()) {
        playerHeadSprite = QPixmap("images/gun2player.png");
    }
    
    emit killCountChanged(scoreboard.getKills(), killGoal);
    emit healthChanged(player.getHealth());
}

void GameController::advanceToLevel3()
{
    level = 3;
    killGoal = 90;  // Need 90 kills to win level 3
    
    // Reset kills and score to 0 for new level
    scoreboard.resetKills();
    scoreboard.incrementScore(-scoreboard.getScore());  // Reset score to 0
    
    // Reset health to 100
    player.setHealth(100);
    
    // Clear entities
    zombies.clear();
    bullets.clear();
    powerups.clear();
    
    // Clear active powerup effects
    shieldActive = false;
    shieldTimer = 0;
    powerUpActive = false;
    powerUpTimer = 0;
    activeBoostTimer = 0;
    activeBoostName = "";
    
    // Update scoreboard
    scoreboard.setKillsToNextLevel(killGoal);
    
    // Reset spawn timers
    zombieSpawnTimer = 0;
    bulletFireTimer = 0;
    
    // Load level 3 gun sprite
    playerHeadSprite = QPixmap(":/images/gun3player.png");
    if (playerHeadSprite.isNull()) {
        playerHeadSprite = QPixmap("images/gun3player.png");
    }
    
    emit killCountChanged(scoreboard.getKills(), killGoal);
    emit healthChanged(player.getHealth());
}

void GameController::setMousePosition(const QPointF &pos)
{
    mousePosition = pos;
}

void GameController::fireBullet()
{
    QPointF playerPos = player.getPosition();
    QPointF delta = mousePosition - playerPos;
    qreal angle = qRadiansToDegrees(qAtan2(delta.y(), delta.x()));
    
    // Bullet speed stays constant (powerup affects fire rate instead)
    float bulletSpeed = 400.0f;
    
    if (level >= 3) {
        // Level 3: Two bullets with 15 degree spread, smaller size, pierce 1
        bullets.push_back(EntityFactory::createBullet(playerPos, angle - 7.5, bulletSpeed, 1));
        bullets.push_back(EntityFactory::createBullet(playerPos, angle + 7.5, bulletSpeed, 1));
        
        // Set sprite to bullet3.png for level 3
        if (!bullets.empty() && bullets.size() >= 2) {
            bullets[bullets.size() - 1]->setSprite(":/images/bullet3.png");
            bullets[bullets.size() - 2]->setSprite(":/images/bullet3.png");
        }
    } else if (level >= 2) {
        // Level 2: Single bullet, pierces 3 zombies, uses bullet2.png
        bullets.push_back(EntityFactory::createBullet(playerPos, angle, bulletSpeed, 3));
    } else {
        // Level 1: Single bullet, pierces 1 zombie, uses bullet1.png
        bullets.push_back(EntityFactory::createBullet(playerPos, angle, bulletSpeed, 1));
    }
}

void GameController::draw(QPainter &p)
{
    // Draw background
    if (!backgroundSprite.isNull()) {
        p.drawPixmap(0, 0, p.device()->width(), p.device()->height(), backgroundSprite);
    } else {
        p.fillRect(0, 0, 800, 600, Qt::darkGray);
    }
    
    QPointF playerPos = player.getPosition();
    
    // Calculate angle from player to mouse
    QPointF delta = mousePosition - playerPos;
    qreal angleToMouse = qRadiansToDegrees(qAtan2(delta.y(), delta.x()));
    
    // Determine if mouse is on right side (for mirroring)
    bool mouseOnRight = delta.x() > 0;
    
    // Calculate head rotation angle (clamped to prevent neck breaking)
    qreal headAngle;
    if (mouseOnRight) {
        // Right side: 0° is straight right, clamp to ±45° (up/down range)
        headAngle = qBound(-45.0, angleToMouse, 45.0);
    } else {
        // Left side: convert angle to be relative to straight left (-180°/180°)
        // When looking left, we want the same ±45° range
        qreal relativeAngle;
        if (angleToMouse > 0) {
            // Upper left quadrant: 90° to 180°
            relativeAngle = angleToMouse - 180.0;  // Convert to -90 to 0
        } else {
            // Lower left quadrant: -90° to -180°
            relativeAngle = angleToMouse + 180.0;  // Convert to 0 to 90
        }
        // Clamp to ±45° and convert back
        relativeAngle = qBound(-45.0, relativeAngle, 45.0);
        headAngle = relativeAngle;  // Use relative angle for left side
    }
    
    // Scale for pixel art (make sprites bigger)
    int bodyWidth = 350;   // Reduced by 100 (was 450)
    int bodyHeight = 300;  // Reduced by 100 (was 400)
    int headWidth = 450;   // Reduced by 100 (was 550)
    int headHeight = 350;  // Decreased height slightly
    
    // Draw player body (centered, no rotation)
    if (!playerBodySprite.isNull()) {
        p.save();
        p.translate(playerPos);
        
        // Mirror body if mouse is on right
        if (mouseOnRight) {
            p.scale(-1, 1);
        }
        
        p.drawPixmap(-bodyWidth/2, -bodyHeight/2, bodyWidth, bodyHeight, playerBodySprite);
        p.restore();
    }
    
    // Draw player head (rotates toward mouse, clamped)
    if (!playerHeadSprite.isNull()) {
        p.save();
        p.translate(playerPos);
        
        // Mirror and rotate head
        if (mouseOnRight) {
            // Mirror horizontally (flip left-right) for right side
            p.scale(-1, 1);
            // Rotate (negative because of the flip)
            p.rotate(-headAngle);
        } else {
            // Left side - no mirror, just rotate
            p.rotate(headAngle);
        }
        
        p.drawPixmap(-headWidth/2, -headHeight/2, headWidth, headHeight, playerHeadSprite);
        p.restore();
    }
    
    // Draw all zombies
    for (const auto& zombie : zombies) {
        QPointF zPos = zombie->getPosition();
        
        // Get current animated sprite for tank zombies, static sprite for others
        const QPixmap& sprite = zombie->getCurrentSprite();
        
        if (!sprite.isNull()) {
            // All zombies are now 70x70
            int size = 70;
            int halfSize = size / 2;
            
            // Mirror all zombies when on left side of screen
            if (zPos.x() < 631 / 2) {
                p.save();
                p.translate(zPos.x(), zPos.y());
                p.scale(-1, 1);  // Flip horizontally
                p.drawPixmap(-halfSize, -halfSize, size, size, sprite);
                p.restore();
            } else {
                p.drawPixmap(zPos.x() - halfSize, zPos.y() - halfSize, size, size, sprite);
            }
        } else {
            // Fallback: draw red circle
            p.setBrush(Qt::red);
            p.drawEllipse(zPos, 20, 20);
        }
    }
    
    // Draw all bullets - size based on level
    for (const auto& bullet : bullets) {
        // Skip drawing if bullet is still invisible (first 0.5 seconds)
        if (!bullet->isVisible()) {
            continue;
        }
        
        QPointF bPos = bullet->getPosition();
        const QPixmap& sprite = bullet->getSprite();
        
        // Level 1 and 3: smaller bullets (600x300), Level 2: bigger bullets (800x400)
        int width = (level == 2) ? 800 : 600;
        int height = (level == 2) ? 400 : 300;
        
        if (!sprite.isNull()) {
            // Draw bullet png sprite
            p.drawPixmap(bPos.x() - width/2, bPos.y() - height/2, width, height, sprite);
        } else {
            // Fallback: draw yellow ellipse if sprite fails to load
            p.setPen(QPen(Qt::red, 10));
            p.setBrush(Qt::yellow);
            p.drawEllipse(bPos, width/2, height/2);
        }
    }
    
    // Draw powerups
    for (const auto& powerup : powerups) {
        if (powerup->isAlive()) {
            QPointF pos = powerup->getPosition();
            const QPixmap& sprite = powerup->getSprite();
            if (!sprite.isNull()) {
                int size = 40;  // Powerup display size (reduced by 10 pixels)
                p.drawPixmap(pos.x() - size/2, pos.y() - size/2, size, size, sprite);
            }
        }
    }
    
    // Draw active powerup icons above player
    // Load sprites for active boosts
    QPixmap healIcon, shieldIcon, powerupIcon;
    healIcon.load(":/images/heal.png");
    shieldIcon.load(":/images/shield.png");
    powerupIcon.load(":/images/powerup.png");
    
    int iconSize = 20;
    int iconSpacing = 20;  // 20 pixel spacing between icons
    
    // Count how many icons are active
    int activeCount = 0;
    if (shieldActive && shieldTimer > 0) activeCount++;
    if (powerUpActive && powerUpTimer > 0) activeCount++;
    if (activeBoostName == "Heal" && activeBoostTimer > 0) activeCount++;
    
    // Calculate starting X to center all icons
    int totalWidth = (activeCount * iconSize) + ((activeCount - 1) * iconSpacing);
    int iconX = playerPos.x() - (totalWidth / 2);
    int iconY = playerPos.y() - 60;  // Above player head
    
    // Draw shield icon if active
    if (shieldActive && shieldTimer > 0) {
        if (!shieldIcon.isNull()) {
            p.drawPixmap(iconX, iconY, iconSize, iconSize, shieldIcon);
            iconX += iconSize + iconSpacing;
        }
    }
    
    // Draw powerup icon if active
    if (powerUpActive && powerUpTimer > 0) {
        if (!powerupIcon.isNull()) {
            p.drawPixmap(iconX, iconY, iconSize, iconSize, powerupIcon);
            iconX += iconSize + iconSpacing;
        }
    }
    
    // Draw heal icon if recently used
    if (activeBoostName == "Heal" && activeBoostTimer > 0) {
        if (!healIcon.isNull()) {
            p.drawPixmap(iconX, iconY, iconSize, iconSize, healIcon);
        }
    }
    
    // Draw powerup slots (bottom left, matching UI slot positions)
    QPixmap healSprite, shieldSprite, powerupSprite;
    healSprite.load(":/images/heal.png");
    shieldSprite.load(":/images/shield.png");
    powerupSprite.load(":/images/powerup.png");
    
    // Draw slot 0 contents
    if (powerupSlots.size() > 0) {
        QPixmap* slotSprite = nullptr;
        if (powerupSlots[0] == PowerUpType::Heal) slotSprite = &healSprite;
        else if (powerupSlots[0] == PowerUpType::Shield) slotSprite = &shieldSprite;
        else slotSprite = &powerupSprite;
        
        if (slotSprite && !slotSprite->isNull()) {
            p.drawPixmap(10, 310, 60, 60, *slotSprite);
        }
    }
    
    // Draw slot 1 contents
    if (powerupSlots.size() > 1) {
        QPixmap* slotSprite = nullptr;
        if (powerupSlots[1] == PowerUpType::Heal) slotSprite = &healSprite;
        else if (powerupSlots[1] == PowerUpType::Shield) slotSprite = &shieldSprite;
        else slotSprite = &powerupSprite;
        
        if (slotSprite && !slotSprite->isNull()) {
            p.drawPixmap(80, 310, 60, 60, *slotSprite);
        }
    }
}

void GameController::handleClick(const QPointF& clickPos)
{
    // Check if clicking on a powerup in the field to use it immediately
    for (auto& powerup : powerups) {
        if (powerup->isAlive() && powerup->contains(clickPos)) {
            activatePowerUp(powerup->getType());
            powerup->setAlive(false);
            return;
        }
    }
}

void GameController::activatePowerUp(PowerUpType type)
{
    if (type == PowerUpType::Heal) {
        player.setHealth(qMin(100, player.getHealth() + 20));
        emit healthChanged(player.getHealth());
        // Show heal icon above player for 2 seconds
        activeBoostName = "Heal";
        activeBoostTimer = 2.0f;
    } else if (type == PowerUpType::Shield) {
        shieldActive = true;
        shieldTimer = 5.0f;
        activeBoostName = "Shield";
        activeBoostTimer = 5.0f;
    } else if (type == PowerUpType::PowerUp) {
        powerUpActive = true;
        powerUpTimer = 5.0f;
        activeBoostName = "Power Up";
        activeBoostTimer = 5.0f;
    }
}

int GameController::getKills() const
{
    return kills;
}

int GameController::getKillGoal() const
{
    return killGoal;
}

int GameController::getScore() const
{
    return scoreboard.getScore();
}
