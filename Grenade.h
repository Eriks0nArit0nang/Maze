#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "Weapon.h"
class Character;

class Grenade : public Weapon
{
    private:
        int velocity;
        int direction;
        int timer;
    
    public:
        Grenade(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher);
        void Update();
        void Detonate();
        void Action(Character * character);
        void Draw(ALLEGRO_BITMAP *buffer, int midX, int midY);
};

#endif
