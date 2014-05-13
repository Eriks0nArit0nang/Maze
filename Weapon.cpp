#include "Weapon.h"
#include "Character.h"
#include <cmath>

Weapon::Weapon(int xPos, int yPos, WeaponProperties weaponProperties):xPos(xPos),yPos(yPos),xPosOrig(xPos),yPosOrig(yPos),properties(weaponProperties){}

Weapon::~Weapon(){}

WeaponProperties &Weapon::GetProperties()
{
    return properties;
}

int Weapon::GetX() const
{
    return (int)round(xPos);
}

int Weapon::GetY() const
{
    return (int)round(yPos);
}

void Weapon::SetX(int x)
{
    xPos = x;
}

void Weapon::SetY(int y)
{
    yPos = y;
}

bool Weapon::WillDestroy()
{
    return destroyThis;
}
