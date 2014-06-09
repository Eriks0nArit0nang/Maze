#include "Bomb.h"
#include "Character.h"
#include <iostream>

Bomb::Bomb(int xPos, int yPos, WeaponProperties weaponProperties):Weapon(xPos, yPos, weaponProperties),timer(40){}

void Bomb::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    
    timer--;
    if (timer == 0)
    {
        Detonate();
    }
}

void Bomb::Detonate()
{
    destroyThis = true;
}

void Bomb::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}
