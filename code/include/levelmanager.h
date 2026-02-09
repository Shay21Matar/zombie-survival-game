#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class LevelManager
{
public:
    LevelManager();

    int getLevel() const { return currentLevel; }

    // called when kills >= required
    bool checkForLevelUp(int currentKills);

private:
    int currentLevel;
};

#endif // LEVELMANAGER_H