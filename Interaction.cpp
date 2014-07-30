#include "Interaction.h"
#include "allegro5/allegro.h"
#include "Globals.h"
#include <iostream>

int Interaction::initialized = 0;

Interaction::Interaction()
{
    if (!initialized)
        Initialize();
    initialized++;
}

Interaction::~Interaction()
{
    initialized--;
}

void Interaction::Initialize()
{
    if (!al_init())
    {
        std::cerr << "Allegro not initialized correctly " << strerror(errno) << std::endl;
    }
    al_install_mouse();
    al_install_keyboard();
    // TODO set up timer - Display class - find appropriate FPS
    // TODO reset display - Display class
    //set_color_depth (desktop_color_depth());
    //set_gfx_mode( GFX_AUTODETECT_WINDOWED, SCREEN_X+GRID_SIZE*2, SCREEN_Y, 0, 0); 
    //set_keyboard_rate(20,0);
}

int Interaction::GetTicks()
{
// TODO modify this to handle event timer properly
    return ticks;
}

void Interaction::ResetTicks()
{
    ticks = 0;
}
