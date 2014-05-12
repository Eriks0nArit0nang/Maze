#ifndef __WEAPONPROPERTIES_H__
#define __WEAPONPROPERTIES_H__ 

#include "WeaponType.h"

class WeaponProperties
{
      private:
              int weaponQuantity;
              int maxQuantity;
              WeaponType type;
              int cost;
              int range;
              int damage;
              int radius;
              int clipSize;
              int fireRate;
              int reloadRate;
              bool active; // Whether The selected Weapon Type is active for purchase/upgrade, use
              
              
      public:
             WeaponProperties(WeaponType type, int maxQuantity);
             WeaponProperties(); // For dummy initializations. Will set to None weapon.
};

/* Defaults
Type		None	Gun		WideShot	ExplodingShot	Grenade		Mine	Nuke	WallBreaker
Cost		0		0		1000		8000			?			?		?		?
Range		0		120		120			120				?			?		?		?
Damage		0		?		?			?				?			?		?		?
Radius		0		2		10			2				?			?		?		?
Clip Size	0		25		25			25				1			1		1		1
Fire Rate	0		10		10			20				200			200		10000	200
Reload Rate	0		?		?			?				0			0		0		0
Active		F		T		T			T				T			T		T		T
*/
  
WeaponProperties::WeaponProperties(){} 
     
#endif
