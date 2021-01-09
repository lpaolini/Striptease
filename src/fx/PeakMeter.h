#ifndef PeakMeter_h
#define PeakMeter_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Timer.h"
#include "AudioChannel.h"
#include "Pixel.h"

class PeakMeter : public Fx {
    private:
        Strip *strip;
        AudioChannel *audioChannel;
        Pixel pixel;
        elapsedMillis beat;

    public:
        PeakMeter(Strip *strip, AudioChannel *audioChannel);
        void loop();
        void reset();
};

#endif
