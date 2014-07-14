#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player : public Character
{
    private:
        void InitializeWeaponProperties();
        static const int HEALTH;
        static const int RADIUS;
        int money;
    public:
        Player(double xPos, double yPos);
        void Attack ();     
        void Move ();
        void Draw (BITMAP *buffer, int midX, int midY);
        void AddMoney(int m);
        int GetMoney() const;
        bool Visit (EnemyWeapon &enemyWeapon);
};

#endif
