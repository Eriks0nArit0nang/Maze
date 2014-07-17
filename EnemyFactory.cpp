#include "EnemyFactory.h"
#include "StandardEnemy.h"
#include "FloatingEnemy.h"
#include <iostream>
#include <ctime>




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
        default:
            std::cerr << "Invalid game type set.  Creating standard enemies only\n";
            return InitializeBasic(health, xPos, yPos);
    }
}

Enemy *EnemyFactory::InitializeBasic(int health, int xPos, int yPos)
{
    int type = rand() % 10;
    if (type >= 0 && type < 10)
        return new StandardEnemy(health,xPos,yPos);
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
    else if (type >= 5 && type < 10)
        return new FloatingEnemy(health,xPos,yPos);
    else
    {
        std::cerr << "EnemyFactory::InitializeBasic has invalid value\n";
        return 0;
    }
}
