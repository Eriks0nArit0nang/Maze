#include "Interaction.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_image.h>
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
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    // TODO set up timer - Display class - find appropriate FPS
}

static int ticks = 0;

int Interaction::GetTicks()
{
// TODO modify this to handle event timer properly
    return ticks;
}

void Interaction::ResetTicks()
{
    ticks = 0;
}
