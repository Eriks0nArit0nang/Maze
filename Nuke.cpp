#include "Nuke.h"
#include "Character.h"

Nuke::Nuke(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):Weapon(xPos, yPos, weaponProperties, watcher)
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
