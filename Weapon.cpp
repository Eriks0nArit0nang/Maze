#include "Weapon.h"
#include "Character.h"
#include <cmath>
Weapon::Weapon(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):xPos(xPos),yPos(yPos),
    xPosOrig(xPos),yPosOrig(yPos),properties(weaponProperties),destroyThis(false),watcher(watcher){}

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

void Weapon::Notify()
{
    watcher->Notify(this);
}

bool Weapon::WillDestroy()
{
    return destroyThis;
}
