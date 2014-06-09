#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <vector>
#include "Weapon.h"
#include "WeaponProperties.h"
#include "WeaponType.h"

#include "AbstractGun.h"
#include "Bomb.h"
#include "Grenade.h"
#include "Nuke.h"
#include "WallBreaker.h"
#include "Globals.h"

class Character
{
    
    protected:
        double xPos,yPos;
        double xVel,yVel;
        int radius;
        WeaponProperties weaponProperties[WEAPON_TYPES]; 
        int health, initialHealth, addedHealth;
        int attackDelay;
        WeaponType activeWeapon;
        std::vector<Weapon *> weapons;
        bool CollideWithWall (char xy, int **grid, int gridSize = GRID_SIZE);
        bool InRange (int weaponX, int weaponY, int radius);

    public:
        void AddHealth (unsigned int h);
        virtual void Attack () = 0;
        Character(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]);
        virtual ~Character() = 0;
        bool Dead();
        WeaponType GetActiveWeapon() const;
        int GetAddedHealth() const;
        int GetHealth() const;
        int GetInitialHealth() const;
        WeaponProperties &GetWeaponProperties(WeaponType type);
        int GetX () const;
        int GetY () const;
        void Hit (int damage);
        virtual void Move () = 0;
        void NextWeapon();
        void PrevWeapon();
        void SetActiveWeapon(WeaponType activeWeapon);
        void SetWeaponProperties(WeaponProperties weaponProperties, WeaponType type);
        void SetX (int x);
        void SetY (int y);
             
        virtual bool Visit (AbstractGun &gun);
        virtual bool Visit (Grenade &grenade);
        virtual bool Visit (Bomb &bomb);
        virtual bool Visit (Nuke &nuke);
        virtual bool Visit (WallBreaker &wallBreaker);
};

#endif
