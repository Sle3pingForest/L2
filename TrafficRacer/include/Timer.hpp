#ifndef Timer_hpp
#define Timer_hpp

#include <stdint.h>
#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();
        virtual ~Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        uint32_t getTicks();
        bool isStarted();
        bool isPaused();
    protected:
    private:
        uint32_t startTicks;
        uint32_t pauseTicks;
        bool started;
        bool paused;
};

#endif /* Timer_hpp */
