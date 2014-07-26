#ifndef __MENU_H__
#define __MENU_H__

class Button;

class Menu
{
    public:
        static void Create(Button* object, void* data);
        static void Play(Button* object, void* data);
        static void Survival(Button* object, void* data);
};
    
#endif
