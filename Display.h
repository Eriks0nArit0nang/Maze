#ifndef __DISPLAY_H__
#define __DISPLAY_H__

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
        
        
    private:
        Display();
        ~Display();
        static Display *instance;
        void InitMainMenu();
        void WallAnimation(int x1, int y1, int x2, int y2, int i);
        int RotateReallignedSprite(BITMAP* screen, BITMAP* sprite, int x, int y, int angle);
        ALLEGRO_TIMER* timer;
        ALLEGRO_DISPLAY *screen;
        ALLEGRO_BITMAP* miniMap;
        ALLEGRO_BITMAP* background;
        ALLEGRO_BITMAP* buffer;
        ALLEGRO_BITMAP* wall;
        ALLEGRO_BITMAP* player;
        ALLEGRO_BITMAP* upgradeScreen;
        ALLEGRO_BITMAP* mainMenu;
        ButtonManager buttonManager;
};

#endif
