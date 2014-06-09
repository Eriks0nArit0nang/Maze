#include "Nuke.h"
#include "Character.h"

Nuke::Nuke(int xPos, int yPos, WeaponProperties weaponProperties):Weapon(xPos, yPos, weaponProperties)
{
    Detonate();
}

void Nuke::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void Nuke::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
}

void Nuke::Detonate()
{
    destroyThis = true;
}
