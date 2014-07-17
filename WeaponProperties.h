#ifndef __WEAPONPROPERTIES_H__
#define __WEAPONPROPERTIES_H__ 

#include "WeaponType.h"
class AbstractGun;
class WideShot;
class ExplodingShot;

class WeaponProperties
{
    friend class WideShot;
    friend class ExplodingShot;
    
    private:
        int weaponQuantity;
        int maxQuantity;
        WeaponType type;
        int cost;
        int range;
        int damage;
        int radius;
        int clipSize;
        int shotsTaken;
        int fireRate;
        int reloadRate;
        bool active; // Whether The selected Weapon Type is active for purchase/upgrade, use
        void Initialize(WeaponType type);
              
    public:
        WeaponProperties(WeaponType type, int maxQuantity);
        WeaponProperties(); // For dummy initializations. Will set to None weapon.
        void AddShotTaken();
        bool GetActive() const;
        int GetCost() const;
        int GetClipSize() const;
        int GetDamage() const;
        int GetFireRate() const;
        int GetMaxQuantity() const;
        int GetRadius() const;
        int GetRange() const;
        int GetReloadRate() const;
        int GetShotsTaken() const;
        WeaponType GetType() const;
        int GetWeaponQuantity() const;
        void SetActive(bool active);
        void SetClipSize(int clipSize);
        void SetFireRate(int fireRate);
        void SetRange(int range);
        void SetWeaponQuantity(int quantity);
};
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
#endif
