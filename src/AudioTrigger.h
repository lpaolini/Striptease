#ifndef AudioTrigger_h
#define AudioTrigger_h

#include "AudioChannel.h"

class AudioTrigger {
    private:
        AudioChannel *audioChannel;
        elapsedMicros timer;

    public:
        AudioTrigger(AudioChannel *audioChannel);
        void reset();
        bool triggered(float noSignalEventsPerSecond = 0, float signalEventsPerSecond = 0);
};

#endif
