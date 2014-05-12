#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <vector>
#include "WeaponProperties.h"
#include "WeaponType.h"

// TODO Once this constant is moved from main.cpp include the appropriate file and remove this.
const int GRID_SIZE = 40;

class Character
{
      private:
              double xPos,yPos;
              double xVel,yVel;
              WeaponProperties weaponProperties[WEAPON_TYPES]; 
              bool CollideWithWall (char xy, int grid[GRID_SIZE][GRID_SIZE]);
              int health, initialHealth, addedHealth;
              WeaponType activeWeapon;

      public:
             void AddHealth (int h);
             virtual void Attack () = 0;
             Character(int health, double xPos, double yPos, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]);
             WeaponType GetActiveWeapon() const;
             int GetAddedHealth() const;
             int GetHealth() const;
             int GetInitialHealth() const;
             WeaponProperties &GetWeaponProperties(WeaponType type);
             int GetX () const;
             int GetY () const;
             void Hit (int damage);
             virtual void Move () = 0;
             void SetActiveWeapon(WeaponType activeWeapon);
             void SetWeaponProperties(WeaponProperties weaponProperties, WeaponType type);
             void SetX (int x);
             void SetY (int y);
};

#endif


class Player
{
      private:
          //    int xRep,yRep;
             
              int clipSize;
              int money;
              int fireRate;
              int range;
              int weaponQuantities[6];
              int maxQuantities[6];
              int weaponCost[6];
              
      public:
           //  Bullet weapon;
             Player ();
             void Add_Money (int n);
             int Get_ClipSize() const;
             
             int Get_Money () const;
             
             int Get_Range () const;
             void Set_Range(int r);
             int Get_Rate() const;
             void Set_Rate(int r);
             void Set_ClipSize(int c);
             bool Max_Quantity (int type);
             void Set_Quantity (int type, int value);
             int Get_Quantity (int type) const;
             int Get_Cost (int type) const;
             
              
};
