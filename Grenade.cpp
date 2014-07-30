#include "Grenade.h"
#include "Character.h"
#include "Map.h"
#include <iostream>
#include <cmath>

Grenade::Grenade(int xPos, int yPos, WeaponProperties weaponProperties, int direction, Character * watcher):
    Weapon(xPos, yPos, weaponProperties, watcher),velocity(6),direction(direction),timer(40){}

void Grenade::Update()
{
    bool changeDir = false;
    
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
    
    int **grid = Map::GetInstance()->GetGrid();
    if (grid[GetX()/BOX_PIXEL_WIDTH][GetY()/BOX_PIXEL_WIDTH] == 1)
    {
        direction = (direction == 1000 || direction == 10) ? (direction / 10) : (direction * 10); // switch direction 1000-100 10-1
        changeDir = true;
        
    }
    
    switch (direction)
    {
        case 1000: // x+
            xPos += velocity;
            break;
        case 100: // x-
            xPos -= velocity;
            break;
        case 10: // y+ (this is actually down)
            yPos += velocity;
            break;
        case 1: // y- (this is actually up)
            yPos -= velocity;
            break;
        default:
            std::cerr << "Invalid grenade direction set\n";
    }
    
    if (changeDir)
        velocity -= 2;
    
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

void Grenade::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    circlefill (buffer, midX+GetX(), midY+GetY(), 2, makecol (0,255,0));
    if (destroyThis)
        circlefill (buffer, midX+GetX(), midY+GetY(), GetProperties().GetRadius(), makecol (255,0,0));
}
