#ifndef __STANDARDENEMY_H__
#define __STANDARDENEMY_H__


#include "Character.h"

class StandardEnemy : public Character
{
    private:
        void InitializeWeaponProperties();
    public:
        StandardEnemy(int health, double xPos, double yPos);
        void Attack ();     
        void Move ();
        void Draw(BITMAP *buffer, int midX, int midY);
        bool Visit (AbstractGun &gun);
        bool Visit (Grenade &grenade);
        bool Visit (Bomb &bomb);
        bool Visit (Nuke &nuke);
};

#endif
