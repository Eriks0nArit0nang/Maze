#ifndef __ENEMYWEAPON_H__
#define __ENEMYWEAPON_H__

#include "Weapon.h"
class Character;

class EnemyWeapon : public Weapon
{
    public:
        EnemyWeapon(int xPos, int yPos, WeaponProperties weaponProperties);
        void Update();
        void Detonate();
        void Action(Character * character);
};

#endif
