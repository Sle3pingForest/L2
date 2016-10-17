#ifndef TIMER_H
#define TIMER_H

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

#endif // TIMER_H
