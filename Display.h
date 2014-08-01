#ifndef __DISPLAY_H__
#define __DISPLAY_H__


struct ALLEGRO_FONT;
#include "Interaction.h"
#include "ButtonManager.h"
#include <allegro5/allegro.h>

class Display : public Interaction
{
    public:
        static Display *GetInstance();
        static void RemoveInstance();
        void DrawUpgrade();
        void NukeAnimation();
        void RemoveWall(int xPos, int yPos);
        void SetBackground();
        void UpdateMiniMap(int centreX, int centreY);
        void UpdateScreen();
        void DrawMainMenu();
        void Zoom(int centreX, int centreY);
        bool UpdateGUI();
        ALLEGRO_DISPLAY* GetDisplay() const;
        
        
    private:
        Display();
        ~Display();
        static Display *instance;
        void InitMainMenu();
        void WallAnimation(int x1, int y1, int x2, int y2, int i);
        ALLEGRO_TIMER* timer;
        ALLEGRO_DISPLAY *screen;
        ALLEGRO_BITMAP* miniMap;
        ALLEGRO_BITMAP* background;
        ALLEGRO_BITMAP* buffer;
        ALLEGRO_BITMAP* upgradeScreen;
        ALLEGRO_BITMAP* mainMenu;
        ALLEGRO_FONT* font;
        ButtonManager buttonManager;
};

#endif
