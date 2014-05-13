#include "AbstractGun.h"
#include "Character.h"

const int AbstractGun::VELOCITY = 2;

AbstractGun::AbstractGun(int xPos, int yPos, WeaponProperties weaponProperties, int direction):Weapon(xPos,yPos,weaponProperties),
    direction(direction){}
    
void AbstractGun::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}
