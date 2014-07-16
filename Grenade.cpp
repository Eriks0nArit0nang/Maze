#include "Grenade.h"
#include "Character.h"
#include <iostream>
#include <cmath>

Grenade::Grenade(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher):
    Weapon(xPos, yPos, weaponProperties, watcher),velocity(6),direction(direction),timer(40){}

void Grenade::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    
    if (std::abs(xPos-xPosOrig) > GetProperties().GetRange()|| std::abs(yPos-yPosOrig) > GetProperties().GetRange())
    {
        delete this;
        return;
    }
    
    switch (direction)
    {
        case 0: // x+
            xPos += velocity;
            break;
        case 1: // x-
            xPos -= velocity;
            break;
        case 2: // y+ (this is actually down)
            yPos += velocity;
            break;
        case 3: // y- (this is actually up)
            yPos -= velocity;
            break;
        default:
            std::cerr << "Invalid grenade direction set\n";
    }
    #ifdef __MAP_H__
    if (Map::GetInstance().IsWall(xPos, yPos))
    {
        direction = (direction / 2) + 1 - (direction % 2); // switch direction 1-0 2-3
        velocity -= 2;
    }
    #endif
    
    timer--;
    if (timer == 0)
    {
        Detonate();
    }
}

void Grenade::Detonate()
{
    destroyThis = true;
}

void Grenade::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void Grenade::Draw(BITMAP *buffer, int midX, int midY)
{
    circlefill (buffer, midX+GetX(), midY+GetY(), 2, makecol (0,255,0));
}
