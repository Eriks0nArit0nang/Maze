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
    public:
        int GetTicks();
        void ResetTicks();
        
};

extern volatile int close_button_pressed;
void close_button_handler(void);
extern volatile int ticks;
void ticker();

#endif
