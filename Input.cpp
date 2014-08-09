#include "Input.h"
#include "Display.h"
Input *Input::instance = 0;

Input::Input():Interaction(),movement(0),weapons(0,0),mouse(0,0),closed(false),time(false),mouseClick(false), forced(0)
{
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(Display::GetInstance()->GetDisplay()));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0/FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
        key[i] = false;
    al_start_timer(timer);
}

Input::~Input()
{
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}

Input *Input::GetInstance()
{
    if (!instance)
        instance = new Input();
    return instance;
}

void Input::RemoveInstance()
{
    delete instance;
    instance = 0;
}

void Input::ReadInput()
{
    ALLEGRO_EVENT event;
    movement = 0;
    weapons.first = 0;
    weapons.second = 0;
    mouse.first = 0;
    mouse.second = 0;
    while (al_get_next_event(event_queue,&event))
    {
        if (event.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            key[event.keyboard.keycode] = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            key[event.keyboard.keycode] = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
            mouseClick = true;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
            mouseClick = false;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            closed = true;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER)
        {
            time = true;
        }
    }
    
    
    if (key[ALLEGRO_KEY_U])
        movement+=10000;
    if (key[ALLEGRO_KEY_RIGHT])
        movement+=1000;
    if (key[ALLEGRO_KEY_LEFT])
        movement+=100;
    if (key[ALLEGRO_KEY_DOWN])
        movement+=10;
    if (key[ALLEGRO_KEY_UP])
        movement+=1;
        
    if (key[ALLEGRO_KEY_D])
        weapons.second=1000;
    else if (key[ALLEGRO_KEY_A])
        weapons.second=100;
    else if (key[ALLEGRO_KEY_S])
        weapons.second=10;
    else if (key[ALLEGRO_KEY_W])
        weapons.second=1;
    
    if (key[ALLEGRO_KEY_LCTRL] || key[ALLEGRO_KEY_RCTRL])
        weapons.second*=2;
    if (key[ALLEGRO_KEY_LSHIFT] || key[ALLEGRO_KEY_RSHIFT])
        weapons.second*=3;
        
    if (key[ALLEGRO_KEY_C])
        weapons.first += 1000;
    if (key[ALLEGRO_KEY_N])
        weapons.first += 100;
    if (key[ALLEGRO_KEY_X])
        weapons.first += 10;
    if (key[ALLEGRO_KEY_Z])
        weapons.first += 1;
    
}

void Input::ReadUpgrade()
{
    ALLEGRO_EVENT event;
    upgrade = 0;
    
    while (al_get_next_event(event_queue,&event))
    {
        if (event.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            key[event.keyboard.keycode] = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            key[event.keyboard.keycode] = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
            mouseClick = true;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouse.first = event.mouse.x;
            mouse.second = event.mouse.y;
            mouseClick = false;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            closed = true;
        }
    }
    
    Display::GetInstance()->UpdateUpgradeMenuGUI();
    
    if (key[ALLEGRO_KEY_U])
        upgrade += 1;
    if (key[ALLEGRO_KEY_F])
        upgrade += 2;
    if (key[ALLEGRO_KEY_C])
        upgrade += 4;
    if (key[ALLEGRO_KEY_R])
        upgrade += 8;
    if (key[ALLEGRO_KEY_H])
        upgrade += 16;
    if (key[ALLEGRO_KEY_N])
        upgrade += 32;    
    if (key[ALLEGRO_KEY_W])
        upgrade += 64;    
    if (key[ALLEGRO_KEY_G])
        upgrade += 128;    
    if (key[ALLEGRO_KEY_E])
        upgrade += 256;    
    if (key[ALLEGRO_KEY_M])
        upgrade += 512;    
    if (key[ALLEGRO_KEY_S])
        upgrade += 1024;   
        
    if (forced != 0)
    {
        key[forced] = false;
        forced = 0;
    }
}    

int Input::GetMovement() const
{
    return movement;
}

int Input::GetUpgrade() const
{
    return upgrade;
}

std::pair<int,int> Input::GetWeapons() const
{
    return weapons;
}

std::pair<int,int> Input::GetMouse() const
{
    return mouse;
}

bool Input::IsPressed (int keyCode) const
{
    return key[keyCode];
}

bool Input::IsClosed () const
{
    return closed;
}

bool Input::IsMouseClicked () const
{
    return mouseClick;
}

bool Input::Timer ()
{
    if (time)
    {
        time = false;
        return true;
    }
    return time;
}

void Input::ForcePressed(int keyCode)
{
    key[keyCode] = true;
    forced = keyCode;
}
