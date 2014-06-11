#ifndef __STANDARDENEMY_H__
#define __STANDARDENEMY_H__


#include "Character.h"

class StandardEnemy : public Character
{
    private:
        void InitializeWeaponProperties();
    public:
        StandardEnemy(int health, double xPos, double yPos, int radius);
        void Attack ();     
        void Move ();
};

#endif
