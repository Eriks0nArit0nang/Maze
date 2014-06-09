#include "Input.h"
#include "allegro.h"

Input *Input::instance = 0;

Input::Input():Interaction(),movement(0),weapons(0,0),mouse(0,0){}

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
    movement = 0;
    weapons.first = 0;
    weapons.second = 0;
    mouse.first = 0;
    mouse.second = 0;
    if (keypressed())
        readkey();
    poll_mouse();
    
    mouse.first = mouse_x;
    mouse.second = mouse_y;
    
    if (key[KEY_U])
        movement+=10000;
    if (key[KEY_RIGHT])
        movement+=1000;
    if (key[KEY_LEFT])
        movement+=100;
    if (key[KEY_DOWN])
        movement+=10;
    if (key[KEY_UP])
        movement+=1;
        
    if (key[KEY_D])
        weapons.second=1000;
    else if (key[KEY_A])
        weapons.second=100;
    else if (key[KEY_S])
        weapons.second=10;
    else if (key[KEY_W])
        weapons.second=1;
        
    if (key[KEY_C])
        weapons.first += 1000;
    if (key[KEY_N])
        weapons.first += 100;
    if (key[KEY_X])
        weapons.first += 10;
    if (key[KEY_Z])
        weapons.first += 1;
    
}

int Input::GetMovement()
{
    return movement;
}

std::pair<int,int> Input::GetWeapons()
{
    return weapons;
}

std::pair<int,int> Input::GetMouse()
{
    return mouse;
}
