#include "Timer.hpp"

Timer::Timer()
{
    started = false;
    paused = false;
    startTicks = 0;
    pauseTicks = 0;
}

Timer::~Timer()
{
    //dtor
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pauseTicks = 0;
}

void Timer::stop()
{
    started = false;
    paused = false;
    startTicks = 0;
    pauseTicks = 0;
}

void Timer::pause()
{
    if(started && !paused)
    {
        started = false;
        paused = true;
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if(paused && !started)
    {
        started = true;
        paused = false;
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;
    }
}

uint32_t Timer::getTicks()
{
    uint32_t time;
    if(started)
    {
        if(paused)
        {
            time = pauseTicks;
        }

        else
        {
            time = SDL_GetTicks() - startTicks;
        }

    }
    return time;
}

bool Timer::isStarted()
{
    return started;
}

bool Timer::isPaused()
{
    return paused;
}
