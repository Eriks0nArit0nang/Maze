#include "Interaction.h"
#include "allegro.h"
#include "Globals.h"

int Interaction::initialized = 0;

Interaction::Interaction():ticks(0)
{
    if (!initialized)
        Initialize();
    initialized++;
}

Interaction::~Interaction()
{
    initialized--;
    if (!initialized)
        allegro_exit();
}

volatile int close_button_pressed = FALSE;

void close_button_handler(void)
{
     close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)


void Interaction::Initialize()
{
    allegro_init();
     
    install_mouse();
    install_keyboard();
    install_timer();
    install_sound(DIGI_AUTODETECT,MIDI_NONE,NULL);
    
    LOCK_VARIABLE(Interaction::ticks);
    LOCK_FUNCTION(Interaction::ticker);
    LOCK_FUNCTION(Interaction::close_button_handler);
    set_close_button_callback(close_button_handler);
    set_color_depth (desktop_color_depth());
    set_gfx_mode( GFX_AUTODETECT, SCREEN_X+GRID_SIZE*2, SCREEN_Y, 0, 0); 
    set_keyboard_rate(20,0);
}

void Interaction::ticker ()
{
     ticks++;
}
END_OF_FUNCTION(ticker);

int Interaction::GetTicks()
{
    return ticks;
}

void Interaction::ResetTicks()
{
    ticks = 0;
}
