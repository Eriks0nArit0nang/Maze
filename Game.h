#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <string>

class Player;
class Enemy;

class Game
{
    public:
        static Game *GetInstance();
        static void RemoveInstance();
        Player *GetPlayer();
        std::vector<Enemy *> &GetEnemies();
        bool Valid(std::string gameName);
        void Play(std::string gameName, int difficulty);
        void Create(std::string gameName, int size);
        std::vector <std::string> GetGameNames() const;
    
    protected:
        static void SetInstance(Game * game);
        Game();
        virtual ~Game();
        void Upgrade();
        
    private:
        virtual void InitLevel(int level, int difficulty, std::string fileName = "");
        void ResetLevel();
        virtual void PlayLevel();
        virtual bool GameEnd();
        static Game *instance;
        Player *player;
        std::vector <Enemy *>enemies;
        std::vector <std::string> gameNames;
        
};

#endif
