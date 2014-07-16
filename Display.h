#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Interaction.h"
#include <allegro.h>

class Display : public Interaction
{
    public:
        static Display *GetInstance();
        static void RemoveInstance();
        void UpdateScreen();
        void DrawUpgrade();
        void SetBackground();
        void UpdateMiniMap(int centreX, int centreY);
        void Zoom(int centreX, int centreY);
        void NukeAnimation();
        
    private:
        Display();
        ~Display();
        static Display *instance;
        int RotateReallignedSprite(BITMAP* screen, BITMAP* sprite, int x, int y, int angle);
        void WallAnimation(int x1, int y1, int x2, int y2, int i);
        BITMAP* miniMap;
        BITMAP* background;
        BITMAP* buffer;
        BITMAP* wall;
        BITMAP* player;
        BITMAP* upgradeScreen;
};

#endif
