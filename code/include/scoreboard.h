#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard
{
public:
    ScoreBoard();

    void incrementScore(int amount = 1);
    int getScore() const;
    void reset();

    // health
    int getHealth() const { return health; }
    void setHealth(int newHealth) { health = newHealth; }

    // level progression goal
    int getKillsToNextLevel() const { return killsToNextLevel; }
    void setKillsToNextLevel(int newKills) { killsToNextLevel = newKills; }

    // NEW – level kill tracking
    void addKill() { kills++; }
    int getKills() const { return kills; }
    void resetKills() { kills = 0; }

    void save();
    void load();

private:
    int score;
    int health;
    int killsToNextLevel;
    int kills;   // NEW
};

#endif // SCOREBOARD_H