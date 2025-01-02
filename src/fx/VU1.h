#ifndef VU1_h
#define VU1_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Timer.h"
#include "audio/AudioChannel.h"
#include "HarmonicMotion.h"
#include "State.h"

class VU1 : public Fx {
    private:
        HarmonicMotion vu;
        HarmonicMotion peak;
        HarmonicMotion peakHold;
        Timer fadeTimer = Timer(10);
        void resetVU();
        void resetPeak();
        void resetPeakHold();

    public:
        VU1(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
