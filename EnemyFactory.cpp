#include "EnemyFactory.h"
#include "StandardEnemy.h"
#include "FloatingEnemy.h"
#include "ShootingEnemy.h"
#include <iostream>
#include <ctime>

static const int SURVIVAL_GAME_TYPE = 10;

EnemyFactory::EnemyFactory(int gameType):gameType(gameType)
{
    std::srand(time(0));
}

Enemy *EnemyFactory::Generate(int health, int xPos, int yPos)
{
    switch (gameType)
    {
        case 1:
            return InitializeBasic(health, xPos, yPos);
        case 2:
            return InitializeMedium(health, xPos, yPos);
        case SURVIVAL_GAME_TYPE:
            return InitializeSurvival(health, xPos, yPos);
        default:
            std::cerr << "Invalid game type set.  Creating basic enemies only\n";
            return InitializeBasic(health, xPos, yPos);
    }
}

Enemy *EnemyFactory::InitializeBasic(int health, int xPos, int yPos)
{
    int type = rand() % 10;
    if (type >= 0 && type < 7)
        return new StandardEnemy(health,xPos,yPos);
    else if (type >= 3 && type < 10)
        return new FloatingEnemy(health,xPos,yPos);
    else
    {
        std::cerr << "EnemyFactory::InitializeBasic has invalid value\n";
        return 0;
    }
}

Enemy *EnemyFactory::InitializeMedium(int health, int xPos, int yPos)
{
    int type = rand() % 10;
    if (type >= 0 && type < 5)
        return new StandardEnemy(health,xPos,yPos);
    else if (type >= 5 && type < 8)
        return new FloatingEnemy(health,xPos,yPos);
    else if (type >= 8 && type < 10)
        return new ShootingEnemy(health,xPos,yPos);
    else
    {
        std::cerr << "EnemyFactory::InitializeMedium has invalid value\n";
        return 0;
    }
}

Enemy *EnemyFactory::InitializeSurvival(int health, int xPos, int yPos)
{
    int type = rand() % 10;
    if (type >= 0 && type < 5)
        return new StandardEnemy(health,xPos,yPos);
    else if (type >= 5 && type < 6)
        return new FloatingEnemy(health,xPos,yPos);
    else if (type >= 6 && type < 10)
        return new ShootingEnemy(health,xPos,yPos);
    else
    {
        std::cerr << "EnemyFactory::InitializeMedium has invalid value\n";
        return 0;
    }
}
