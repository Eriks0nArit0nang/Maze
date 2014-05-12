#include "Weapon.h"


Weapon::Weapon(int xPos, int yPos, WeaponProperties weaponProperties):xPos(xPos),yPos(yPos),xPosOrig(xPos),yPosOrig(yPos),weaponProperties(weaponProperties){}

Weapon::~Weapon(){}

void Weapon::Action( Character * character)
{
    if (character.Visit(*this))
    {
        destroyThis = true;
    }
}

WeaponProperties Weapon::GetProperties() const
{
    return weaponProperties;
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
