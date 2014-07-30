#ifndef __BOMB_H__
#define __BOMB_H__

#include "Weapon.h"
class Character;

class Bomb : public Weapon
{
    private:
        int timer;
    
    public:
        Bomb(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher);
        void Update();
        void Detonate();
        void Action(Character *character);
        void Draw(ALLEGRO_BITMAP *buffer, int midX, int midY);
};

#endif
