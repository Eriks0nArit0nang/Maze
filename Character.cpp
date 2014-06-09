#include "Character.h"
#include "WeaponProperties.h"
#include <cmath>

using namespace std;

void Character::AddHealth (unsigned int h)
{
     health += h;
     addedHealth += h;
}

Character::Character(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]):
                         xPos(xPos),yPos(yPos),xVel(0),yVel(0),radius(radius),health(health),initialHealth(health),addedHealth(0),
						 activeWeapon(activeWeapon)
{
 	for (int i = 0; i < WEAPON_TYPES; i++)
 		this->weaponProperties[i] = weaponProperties[i];
}

Character::~Character()
{
    for (unsigned int i = 0; i < weapons.size(); i++)
        delete weapons[i];
}

bool Character::CollideWithWall (char xy, int ** grid, int size)
{
     if ( abs (GetX() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) > BOX_PIXEL_WIDTH/2 - radius && abs (GetY() % BOX_PIXEL_WIDTH - BOX_PIXEL_WIDTH/2) > BOX_PIXEL_WIDTH/2 - radius)
     {
        return (grid[((int)round(xPos+xVel+xVel/abs(xVel)*radius))/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] == 1 || 
                grid[GetX()/BOX_PIXEL_WIDTH][((int)round(yPos+yVel+yVel/abs(yVel)*radius))/BOX_PIXEL_WIDTH] == 1 ||
                grid[((int)round(xPos+xVel+xVel/abs(xVel)*radius))/BOX_PIXEL_WIDTH][((int)round(yPos+yVel+yVel/abs(yVel)*radius))/BOX_PIXEL_WIDTH]==1);
     }
     if (xy == 'x' && xVel != 0)
        return grid[((int)round(xPos+xVel+xVel/abs(xVel)*radius))/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] == 1;
     else if (xy == 'y' && yVel != 0)
          return grid[GetX()/BOX_PIXEL_WIDTH][((int)round(yPos+yVel+yVel/abs(yVel)*radius))/BOX_PIXEL_WIDTH] == 1;
     return false;
}

bool Character::Dead()
{
    return health <= 0;
}

WeaponType Character::GetActiveWeapon() const
{
    return activeWeapon;
}

int Character::GetAddedHealth() const
{
    return addedHealth;
}

int Character::GetHealth() const
{
    return health;
}

int Character::GetInitialHealth() const
{
    return initialHealth;
}

WeaponProperties &Character::GetWeaponProperties(WeaponType type)
{
    return weaponProperties[type];
}

int Character::GetX () const
{
    return static_cast<int>(round(xPos));
}

int Character::GetY () const
{
    return static_cast<int>(round(yPos));
}

void Character::Hit (int damage)
{
     health -= damage;
     if (health < 0)
        health = 0;
}

bool Character::InRange(int weaponX, int weaponY, int radius)
{
    return sqrt( pow(weaponX-xPos, 2) + pow(weaponY-yPos, 2) ) < radius + this->radius;
}

void Character::SetActiveWeapon(WeaponType activeWeapon)
{
     this->activeWeapon = activeWeapon;
}

void Character::SetWeaponProperties(WeaponProperties weaponProperties, WeaponType type)
{
     this->weaponProperties[type] = weaponProperties;
}

void Character::SetX (int x)
{
     this->xPos = x;
}

void Character::SetY (int y)
{
     this->yPos = y;
}

bool Character::Visit (AbstractGun &gun)
{
    if (InRange(gun.GetX(), gun.GetY(), gun.GetProperties().GetRadius()))
    {
        Hit(gun.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Character::Visit (Grenade &grenade)
{
    if (InRange(grenade.GetX(), grenade.GetY(), grenade.GetProperties().GetRadius()))
    {
        Hit(grenade.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Character::Visit (Bomb &bomb)
{
    if (InRange(bomb.GetX(), bomb.GetY(), bomb.GetProperties().GetRadius()))
    {
        Hit(bomb.GetProperties().GetDamage());
        return true;
    }
    return false;
}

bool Character::Visit (Nuke &nuke)
{
    if (InRange(nuke.GetX(), nuke.GetY(), nuke.GetProperties().GetRange()))
    {
        Hit(nuke.GetProperties().GetDamage());
    }
    return false;
}

bool Character::Visit (WallBreaker &wallBreaker)
{
    return false;
    // wall breaker doesn't affect characters
}
