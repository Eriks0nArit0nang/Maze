#ifndef __INTERACTION_H__
#define __INTERACTION_H__

class Interaction
{
    private:
        static void Initialize();
        static int initialized;
    protected:
        Interaction();
        virtual ~Interaction() = 0;  
        volatile int ticks;  // for timer
        void ticker();
        
};

#endif
