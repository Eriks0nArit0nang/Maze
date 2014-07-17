#include "Enemy.h"

Enemy::Enemy(int health, double xPos, double yPos, int radius, WeaponType activeWeapon):
    Character(health, xPos, yPos, radius, activeWeapon){}

bool Enemy::Visit (AbstractGun &gun)
{
    if (InRange(gun.GetX(), gun.GetY(), gun.GetProperties().GetRadius()))
    {
        Hit(gun.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Enemy::Visit (Grenade &grenade)
{
    if (InRange(grenade.GetX(), grenade.GetY(), grenade.GetProperties().GetRadius()) && grenade.WillDestroy())
    {
        Hit(grenade.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Enemy::Visit (Bomb &bomb)
{
    if (InRange(bomb.GetX(), bomb.GetY(), bomb.GetProperties().GetRadius()))
    {
        Hit(bomb.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Enemy::Visit (Nuke &nuke)
{
    if (InRange(nuke.GetX(), nuke.GetY(), nuke.GetProperties().GetRadius()))
    {
        Hit(nuke.GetProperties().GetDamage());
    }
    return false;
}
