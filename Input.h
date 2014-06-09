#ifndef __INPUT_H__
#define __INPUT_H__

#include <utility>
#include "Interaction.h"

class Input : public Interaction
{
    public:
        static Input *GetInstance();
        void ReadInput();
        int GetMovement();
        std::pair<int,int> GetWeapons();
        std::pair <int,int> GetMouse();
        static void RemoveInstance();
        
        
    private:
        static Input *instance;
        Input();
        int movement;
        std::pair<int,int> weapons; // special weapons, direction
        std::pair<int,int> mouse;
    
    
};

#endif
