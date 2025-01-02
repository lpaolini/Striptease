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
        bool triggered(double noSignalEventsPerSecond = 0, double signalEventsPerSecond = 0);
};

#endif
