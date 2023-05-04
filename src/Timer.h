#ifndef TIMER_H
#define TIMER_H
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

    // Gets the timer's time
    Uint32 getTicks();

    // Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;

    bool mPaused;
    bool mStarted;
};

#endif // TIMER_H
