#include "EnemyWeapon.h"
#include "Character.h"

EnemyWeapon::EnemyWeapon(int xPos, int yPos, WeaponProperties weaponProperties):Weapon(xPos, yPos, weaponProperties)
{
    Detonate();
}

void EnemyWeapon::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void EnemyWeapon::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
}

void EnemyWeapon::Detonate()
{
    destroyThis = true;
}
