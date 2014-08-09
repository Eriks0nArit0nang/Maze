#ifndef __UPGRADEMENU_H__
#define __UPGRADEMENU_H__

class Button;
#include "ButtonManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class UpgradeMenu
{
    private:
        ALLEGRO_BITMAP *upgradeMenu;
        ALLEGRO_FONT *font;
        ButtonManager buttonManager;
        void Init(ALLEGRO_BITMAP *buffer);
    
    public:
        UpgradeMenu(ALLEGRO_BITMAP *buffer);
        ~UpgradeMenu();
        void Draw(ALLEGRO_BITMAP *screen);
        ButtonManager &GetButtonManager();
        static void Health(Button* object, void* data);
        static void FireRate(Button* object, void* data);
        static void ClipSize(Button* object, void* data);
        static void Range(Button* object, void* data);
        static void Nuke(Button* object, void* data);
        static void WideShot(Button* object, void* data);
        static void ExplodingShot(Button* object, void* data);
        static void WallBreaker(Button* object, void* data);
        static void Mine(Button* object, void* data);
        static void Grenade(Button* object, void* data);
        static void Resume(Button* object, void* data);
    
    
};

#endif
