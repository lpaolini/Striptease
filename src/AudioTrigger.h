#ifndef AudioTrigger_h
#define AudioTrigger_h

#include "AudioChannel.h"

class AudioTrigger {
    private:
        AudioChannel *audioChannel;
        bool beatDetected;
        elapsedMicros timer;

    public:
        AudioTrigger(AudioChannel *audioChannel);
        void reset();
        void loop();
        bool triggered(float noSignalEventsPerSecond = 0, float signalEventsPerSecond = 0);
};

#endif
