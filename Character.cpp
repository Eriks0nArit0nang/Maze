#include "Character.h"
#include <cmath>

using namespace std;

void Character::AddHealth (int h)
{
     health += h;
     addedHealth += h;
}

Character::Character(int health, double xPos, double yPos, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]):
                         xPos(xPos),yPos(yPos),xVel(0),yVel(0),health(health),initialHealth(health),addedHealth(0),
						 activeWeapon(activeWeapon)
{
 	for (int i = 0; i < WEAPON_TYPES; i++)
 		this->weaponProperties[i] = weaponProperties[i];
}

bool Character::CollideWithWall (char xy, int grid[GRID_SIZE][GRID_SIZE])
{
     if ( abs (GetX() % 60 - 30) > 25 && abs (GetY() % 60 - 30) > 25)
     {
        return (grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][GetY()/60] == 1 || 
                grid[GetX()/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60] == 1 ||
                grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60]==1);
     }
     if (xy == 'x' && xVel != 0)
        return grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][GetY()/60] == 1;
     else if (xy == 'y' && yVel != 0)
          return grid[GetX()/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60] == 1;
     return false;
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
