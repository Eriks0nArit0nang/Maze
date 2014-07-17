#include "WeaponProperties.h"
#include <iostream>

// This method exists as array initialization.  It should not be used in any other context
WeaponProperties::WeaponProperties():weaponQuantity(0),maxQuantity(0),type(_None),shotsTaken(0)
{
    Initialize(type);								
} 

WeaponProperties::WeaponProperties(WeaponType type, int maxQuantity):weaponQuantity(0),maxQuantity(maxQuantity),type(type),shotsTaken(0)
{
    Initialize(type);										  
}

WeaponProperties::WeaponProperties(WeaponType type, int maxQuantity, int defaultQuantity):weaponQuantity(defaultQuantity),maxQuantity(maxQuantity),type(type),shotsTaken(0)
{
    Initialize(type);	// Only for testing									  
}

void WeaponProperties::AddShotTaken()
{
    shotsTaken++;
    if (shotsTaken > clipSize)
        shotsTaken -= clipSize;
}

bool WeaponProperties::GetActive() const
{
    return active;
}

int WeaponProperties::GetCost() const
{
    return cost;
}

int WeaponProperties::GetClipSize() const
{
    return clipSize;
}

int WeaponProperties::GetDamage() const
{
    return damage;
}

int WeaponProperties::GetFireRate() const
{
    return fireRate;
}

int WeaponProperties::GetMaxQuantity() const
{
    return maxQuantity;
}

int WeaponProperties::GetRadius() const
{
    return radius;
}

int WeaponProperties::GetRange() const
{
    return range;
}

int WeaponProperties::GetReloadRate() const
{
    return reloadRate;
}

int WeaponProperties::GetShotsTaken() const
{
    return shotsTaken;
}

WeaponType WeaponProperties::GetType() const
{
    return type;
}

int WeaponProperties::GetWeaponQuantity() const
{
    return weaponQuantity;
}

/* Defaults
Type		None	Gun		WideShot	ExplodingShot	Grenade		Mine	Nuke	WallBreaker
Cost		0		0		1000		8000			300			1000	10000	5000
Range		0		120		120			120				240			0		0		600
Damage		0		10		15			20				80			200		1000	0
Radius		0		1		3			20				30			5		400		0
Clip Size	0		25		25			25				1			1		1		1
Fire Rate	0		10		10			20				200			200		10000	200
Reload Rate	0		60		60			60				0			0		0		0
Active		F		T		T			T				T			T		T		T
*/
void WeaponProperties::Initialize(WeaponType type)
{
    switch (type)
    {
        case _None:
            cost = 0;
            range = 0;
            damage = 0;
            radius = 0;
            clipSize = 0;
            fireRate = 0;
            reloadRate = 0;
            active = false;
            break;
        case _Gun:
            cost = 0;
            range = 120;
            damage = 10;
            radius = 1;
            clipSize = 25;
            fireRate = 10;
            reloadRate = 60;
            active = true;
            break;
        case _WideShot:
            cost = 1000;
            range = 120;
            damage = 15;
            radius = 3;
            clipSize = 25;
            fireRate = 10;
            reloadRate = 60;
            active = true;
            break;
        case _ExplodingShot:
            cost = 8000;
            range = 120;
            damage = 20;
            radius = 20; // only after contact.  Implemented in separate class.
            clipSize = 25;
            fireRate = 20;
            reloadRate = 60;
            active = true;
            break;
        case _Grenade:
            cost = 300;
            range = 240;
            damage = 80;
            radius = 30;
            clipSize = 1;
            fireRate = 50;
            reloadRate = 0;
            active = true;
            break;
        case _Mine:
            cost = 1000;
            range = 0;
            damage = 200;
            radius = 30;
            clipSize = 1;
            fireRate = 10;
            reloadRate = 0;
            active = true;
            break;
        case _Nuke:
            cost = 10000;
            range = 0;
            damage = 1000; // > MAX_HEALTH of an enemy
            radius = 400;
            clipSize = 1;
            fireRate = 100;
            reloadRate = 0;
            active = true;
            break;
        case _WallBreaker:
            cost = 5000;
            range = 600;
            damage = 0;
            radius = 0;
            clipSize = 1;
            fireRate = 10;
            reloadRate = 0;
            active = true;
            break;
        case _Enemy:
            cost = 0;
            range = 1;
            damage = 5;
            radius = 10;
            clipSize = 1;
            fireRate = 10;
            reloadRate = 0;
            active = false;
            break;
        default:
            std::cerr << "The selected weapon type does not have an initializer.\n"; 
    }
}

void WeaponProperties::SetActive(bool active)
{
    this->active = active;
}

void WeaponProperties::SetClipSize(int clipSize)
{
    this->clipSize = clipSize;
}

void WeaponProperties::SetFireRate(int fireRate)
{
    this->fireRate = fireRate;
}

void WeaponProperties::SetRange(int range)
{
    this->range = range;
}

void WeaponProperties::SetWeaponQuantity(int quantity)
{
    weaponQuantity = quantity;
}
