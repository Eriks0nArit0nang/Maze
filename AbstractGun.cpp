#include "AbstractGun.h"

AbstractGun::AbstractGun(int xPos, int yPos, WeaponProperties weaponProperties, int direction):Weapon(xPos,yPos,weaponProperties),
    direction(direction){}
