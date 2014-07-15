#include "AbstractGun.h"
#include "Character.h"

const int AbstractGun::VELOCITY = 2;

AbstractGun::AbstractGun(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher):
    Weapon(xPos,yPos,weaponProperties,watcher),direction(direction){}
    
void AbstractGun::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}
