#ifndef __SURVIVALGAME_H__
#define __SURVIVALGAME_H__

#include "Game.h"
class EnemyFactory;

class SurvivalGame : public Game
{
    public:
        static Game *NewInstance();

    protected:
        SurvivalGame();
        ~SurvivalGame();
    
    private:
        void InitLevel(int level, int difficulty, std::string fileName = "");
        void PlayLevel();
        bool GameEnd();
        EnemyFactory *enemyFactory;
};

#endif
