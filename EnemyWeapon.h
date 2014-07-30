#ifndef __ENEMYWEAPON_H__
#define __ENEMYWEAPON_H__

#include "Weapon.h"
class Character;

class EnemyWeapon : public Weapon
{
    public:
        EnemyWeapon(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher);
        ~EnemyWeapon();
        void Update();
        void Detonate();
        void Action(Character * character);
        void Draw(ALLEGRO_BITMAP *buffer, int midX, int midY);
};

#endif
