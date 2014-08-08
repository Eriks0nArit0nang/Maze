#ifndef __MaiNMENU_H__
#define __MAINMENU_H__

class Button;

class MainMenu
{
    public:
        static void Create(Button* object, void* data);
        static void Play(Button* object, void* data);
        static void Survival(Button* object, void* data);
};
    
#endif
