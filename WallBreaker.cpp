#include "Wallbreaker.h"
#include "Character.h"
#include "Globals.h"
#include <cmath>
#include <iostream>


const int WallBreaker::VELOCITY = BOX_PIXEL_WIDTH;

WallBreaker::WallBreaker(int xPos, int yPos, WeaponProperties weaponProperties, int direction):Weapon(xPos,yPos,weaponProperties),direction(direction){}

void WallBreaker::Action(Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void WallBreaker::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    
    if (std::abs(xPos-xPosOrig) > GetProperties().GetRange() || std::abs(yPos-yPosOrig) > GetProperties().GetRange())
    {
        delete this;
        return;
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
            std::cerr << "Invalid wall breaker direction set\n";
    }
}

void WallBreaker::Detonate()
{
    destroyThis = true;
}
