#include "Gun.h"
#include "Character.h"
#include "Map.h"
#include "Globals.h"
#include <iostream>
#include <cmath>
#include <allegro5/allegro_primitives.h>

Gun::Gun(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher):
    AbstractGun(xPos,yPos,weaponProperties,direction,watcher){}
        
void Gun::Update()
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
            std::cerr << "Invalid gun direction set\n";
    }
}

void Gun::Detonate()
{
    destroyThis = true;
}

void Gun::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void Gun::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    al_set_target_bitmap(buffer);
    al_draw_line (midX+GetX(), midY+GetY(), midX+(int)round(xPosOrig), midY+(int)round(yPosOrig), al_map_rgb (255,0,0), 0);
}
