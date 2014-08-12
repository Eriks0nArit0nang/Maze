#ifndef __MaiNMENU_H__
#define __MAINMENU_H__

class Button;
#include "ButtonManager.h"
#include <string>
#include <allegro5/allegro.h>

class MainMenu
{
    private:
        static std::string ReadString(int yCoord, int type);
        static int ReadSize();
        static int ReadDifficulty();
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
        static void Larger(Button* object, void* data);
        static void Smaller(Button* object, void* data);
        static void SetClose(Button* object, void* data);
        static void Beginner(Button* object, void* data);
        static void Easy(Button* object, void* data);
        static void Medium(Button* object, void* data);
        static void Hard(Button* object, void* data);
        static void Expert(Button* object, void* data);
};
    
#endif
