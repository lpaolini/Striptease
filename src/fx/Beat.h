#ifndef Beat_h
#define Beat_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "Fx.h"
#include "Timer.h"
#include "HarmonicMotion.h"

class Beat : public Fx {
    private:
        AudioTrigger *audioTrigger;
        HarmonicMotion peak;
        HarmonicMotion peakHold;
        HarmonicMotion peakHoldSlow;
        Timer timer = Timer(10);

    public:
        Beat(Strip *strip, AudioChannel *audioChannel);
        ~Beat();
        void loop();
        void reset();
};

#endif
