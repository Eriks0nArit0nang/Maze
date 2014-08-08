#ifndef __MaiNMENU_H__
#define __MAINMENU_H__

class Button;
#include "ButtonManager.h"
#include <string>
#include <allegro5/allegro.h>

class MainMenu
{
    private:
        static std::string ReadString(int yCoord);
        ALLEGRO_BITMAP *mainMenu;
        ButtonManager buttonManager;
        void Init(ALLEGRO_BITMAP *buffer);
        
    public:
        MainMenu(ALLEGRO_BITMAP *buffer);
        ~MainMenu();
        void Draw(ALLEGRO_BITMAP *screen);
        ButtonManager &GetButtonManager();
        static void Create(Button* object, void* data);
        static void Play(Button* object, void* data);
        static void Survival(Button* object, void* data);
        
};
    
#endif
