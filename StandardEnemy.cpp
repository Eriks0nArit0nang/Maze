#include "StandardEnemy.h"

StandardEnemy::StandardEnemy(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]):
    Character(health, xPos, yPos, radius, activeWeapon, weaponProperties){}

void StandardEnemy::Attack ()
{
    // TODO
}     

void StandardEnemy::Move ()
{
    // TODO
}
