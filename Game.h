#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <string>

class Player;
class StandardEnemy;

class Game
{
    public:
        static Game *GetInstance();
        static void RemoveInstance();
        Player *GetPlayer();
        std::vector<StandardEnemy *> &GetEnemies();
        void Play(std::string gameName, int difficulty);
        void Create(std::string gameName);
        
        
    private:
        Game();
        void InitLevel(int level, int difficulty);
        void ResetLevel();
        void PlayLevel();
        bool GameEnd();
        static Game *instance;
        Player *player;
        std::vector <StandardEnemy *>enemies;
        
};

#endif
