#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Interaction.h"
#include <allegro.h>

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
        void Zoom(int centreX, int centreY);
        
        
    private:
        Display();
        ~Display();
        static Display *instance;
        void WallAnimation(int x1, int y1, int x2, int y2, int i);
        int RotateReallignedSprite(BITMAP* screen, BITMAP* sprite, int x, int y, int angle);
        BITMAP* miniMap;
        BITMAP* background;
        BITMAP* buffer;
        BITMAP* wall;
        BITMAP* player;
        BITMAP* upgradeScreen;
};

#endif
