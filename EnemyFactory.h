#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__

class Enemy;

class EnemyFactory
{
    public:
        EnemyFactory(int gameType);
        Enemy *Generate(int health, int xPos, int yPos);
    private:
        int gameType;
        Enemy *InitializeBasic(int health, int xPos, int yPos);
        Enemy *InitializeMedium(int health, int xPos, int yPos);
        Enemy *InitializeHard(int health, int xPos, int yPos);
        Enemy *InitializeSurvival(int health, int xPos, int yPos);
};

#endif
