#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer {
    private:
        unsigned long last;
        unsigned int duration;
        bool running;
        bool autoReset;

    public:
        explicit Timer(unsigned long duration, bool autoReset = true);
        void stop();
        void reset();
        void reset(unsigned long duration);
        bool isElapsed();
        bool isElapsed(unsigned long duration);
        bool isRunning();
};

#endif
