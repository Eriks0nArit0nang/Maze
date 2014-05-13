#include "Gun.h"
#include <iostream>
#include <cmath>

Gun::Gun(int xPos, int yPos, WeaponProperties weaponProperties, int direction):AbstractGun(xPos,yPos,weaponProperties,direction){}
        
void Gun::Update()
{
    if (destroyThis)
    {
        delete this;
    }
    
    if (std::abs(xPos-xPosOrig) > GetProperties().GetRange() || std::abs(yPos-yPosOrig) > GetProperties().GetRange())
    {
        delete this;
    }
    
    switch (direction)
    {
        case 0: // x+
            xPos += VELOCITY;
            break;
        case 1: // x-
            xPos -= VELOCITY;
            break;
        case 2: // y+ (this is actually down)
            yPos += VELOCITY;
            break;
        case 3: // y- (this is actually up)
            yPos -= VELOCITY;
            break;
        default:
            std::cerr << "Invalid gun direction set\n";
    }
}

void Gun::Detonate()
{
    destroyThis = true;
}
