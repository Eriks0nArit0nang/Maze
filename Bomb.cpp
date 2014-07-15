#include "Bomb.h"
#include "Character.h"
#include <iostream>

Bomb::Bomb(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):
    Weapon(xPos, yPos, weaponProperties, watcher),timer(200){}

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
