#ifndef __INPUT_H__
#define __INPUT_H__

#include <utility>
#include "Interaction.h"
#include "allegro5/allegro.h"

class Input : public Interaction
{
    public:
        static Input *GetInstance();
        void ReadInput();
        void ReadUpgrade();
        int GetMovement() const;
        int GetUpgrade() const;
        std::pair<int,int> GetWeapons() const;
        std::pair <int,int> GetMouse() const;
        bool IsClosed() const;
        bool IsPressed(int keyCode) const;
        bool IsMouseClicked() const;
        bool Timer();
        static void RemoveInstance();
        void ForcePressed(int keyCode);
        
        
    private:
        static Input *instance;
        Input();
        ~Input();
        bool key[ALLEGRO_KEY_MAX];
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_TIMER *timer;
        int movement;
        int upgrade;
        std::pair<int,int> weapons; // special weapons, direction
        std::pair<int,int> mouse;
        bool mouseClick;
        bool closed;
        bool time;
        int forced;
};

#endif
