#include "WallBreaker.h"
#include "Character.h"
#include "Globals.h"
#include "Map.h"
#include "Display.h"
#include <cmath>
#include <iostream>


const int WallBreaker::VELOCITY = BOX_PIXEL_WIDTH;

WallBreaker::WallBreaker(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher):
    Weapon(xPos,yPos,weaponProperties, watcher),direction(direction){}

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
        destroyThis = true;
        return;
    }
    
    int **grid = Map::GetInstance()->GetGrid();
    if (grid[GetX()/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] == 1)
    {
        destroyThis = true;
        if (abs(GetX()/BOX_PIXEL_WIDTH-GRID_SIZE/2+1) < GRID_SIZE/2 - 5 && abs(GetY()/BOX_PIXEL_WIDTH - GRID_SIZE/2+1) < GRID_SIZE/2 - 5)
        {
            grid[GetX()/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] = 0;
            Display::GetInstance()->RemoveWall(GetX(),GetY());
        }
        return;
    }
    
    switch (direction)
    {
        case 1000: // x+
            xPos += VELOCITY;
            break;
        case 100: // x-
            xPos -= VELOCITY;
            break;
        case 10: // y+ (this is actually down)
            yPos += VELOCITY;
            break;
        case 1: // y- (this is actually up)
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

void WallBreaker::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    
}
