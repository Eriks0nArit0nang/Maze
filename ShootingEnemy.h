#ifndef __SHOOTINGENEMY_H__
#define __SHOOTINGENEMY_H__


#include "Enemy.h"

class ShootingEnemy : public Enemy
{
    private:
        void InitializeWeaponProperties();
    public:
        ShootingEnemy(int health, double xPos, double yPos);
        void Attack ();     
        void Move ();
        void Draw(BITMAP *buffer, int midX, int midY);

};

#endif
