#ifndef __INPUT_H__
#define __INPUT_H__

#include <utility>
#include "Interaction.h"

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
        static void RemoveInstance();
        
        
    private:
        static Input *instance;
        Input();
        int movement;
        int upgrade;
        std::pair<int,int> weapons; // special weapons, direction
        std::pair<int,int> mouse;
    
    
};

#endif
