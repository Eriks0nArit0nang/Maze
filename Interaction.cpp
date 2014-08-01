#include "Interaction.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include <iostream>

int Interaction::FPS = 40;

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
    if (!initialized)
        UnInitialize();
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
}

void Interaction::UnInitialize()
{
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_uninstall_system();
}
