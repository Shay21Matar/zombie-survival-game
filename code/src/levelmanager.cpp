#include "LevelManager.h"

LevelManager::LevelManager()
    : currentLevel(1)
{
}

// Always increments level when called.
// (GameController already checked kill requirements)
bool LevelManager::checkForLevelUp(int /*currentKills*/)
{
    currentLevel++;
    return true;
}