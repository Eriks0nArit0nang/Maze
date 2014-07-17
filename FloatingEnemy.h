#ifndef __FLOATINGENEMY_H__
#define __FLOATINGENEMY_H__


#include "Enemy.h"

class FloatingEnemy : public Enemy
{
    private:
        void InitializeWeaponProperties();
    public:
        FloatingEnemy(int health, double xPos, double yPos);
        void Attack ();     
        void Move ();
        void Draw(BITMAP *buffer, int midX, int midY);

};

#endif
