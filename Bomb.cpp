#include "Bomb.h"
#include "Character.h"
#include <iostream>

Bomb::Bomb(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):
    Weapon(xPos, yPos, weaponProperties, watcher),timer(200){}

void Bomb::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    
    timer--;
    if (timer == 0)
    {
        Detonate();
    }
}

void Bomb::Detonate()
{
    destroyThis = true;
}

void Bomb::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void Bomb::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    al_set_target_bitmap(buffer);
    al_draw_filled_circle (midX+GetX(), midY+GetY(), 2, al_map_rgb (125,0,0));
    if (destroyThis)
        al_draw_filled_circle (midX+GetX(), midY+GetY(), GetProperties().GetRadius(), al_map_rgb (255,0,0));
}
