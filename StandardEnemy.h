#ifndef __STANDARDENEMY_H__
#define __STANDARDENEMY_H__


#include "Enemy.h"

class StandardEnemy : public Enemy
{
    private:
        void InitializeWeaponProperties();
    public:
        StandardEnemy(int health, double xPos, double yPos);
        void Attack ();     
        void Move ();
        void Draw(ALLEGRO_BITMAP *buffer, int midX, int midY);

};

#endif
