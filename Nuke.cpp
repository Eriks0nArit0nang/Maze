#include "Nuke.h"
#include "Character.h"
#include "Display.h"

Nuke::Nuke(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):Weapon(xPos, yPos, weaponProperties, watcher)
{
    
}

void Nuke::Action( Character * character)
{
    if (character->Visit(*this))
    {
        destroyThis = true;
    }
}

void Nuke::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    else
        Detonate();
}

void Nuke::Detonate()
{
    destroyThis = true;
}

void Nuke::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    Display::GetInstance()->NukeAnimation();
}
