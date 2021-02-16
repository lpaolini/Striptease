#ifndef VU1_h
#define VU1_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Timer.h"
#include "AudioChannel.h"
#include "HarmonicMotion.h"

class VU1 : public Fx {
    private:
        HarmonicMotion peak;
        HarmonicMotion peakHold;
        Timer fadeTimer = Timer(10);
        void resetPeak();
        void resetPeakHold();

    public:
        VU1(Strip *strip, AudioChannel *audioChannel);
        void loop();
        void reset();
};

#endif
