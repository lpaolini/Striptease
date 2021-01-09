#ifndef Beat_h
#define Beat_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Timer.h"
#include "HarmonicMotion.h"

class Beat : public Fx {
    private:
        Strip *strip;
        AudioChannel *audioChannel;
        HarmonicMotion peak;
        HarmonicMotion peakHold;
        HarmonicMotion peakHoldSlow;
        Timer timer = Timer(10);

    public:
        Beat(Strip *strip, AudioChannel *audioChannel);
        void loop();
        void reset();
};

#endif
