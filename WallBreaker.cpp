#include "Wallbreaker.h"
#include "Character.h"
#include <cmath>
#include <iostream>

// TODO remove once linked properly into a global values file
const int BOX_PIXEL_WIDTH = 60;


const int WallBreaker::VELOCITY = BOX_PIXEL_WIDTH;

        int direction;

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
            std::cerr << "Invalid wall breaker direction set\n";
    }
}

void WallBreaker::Detonate()
{
    destroyThis = true;
}
