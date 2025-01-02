#ifndef RippleReflections_h
#define RippleReflections_h

#include <Arduino.h>
#include <FastLED.h>
#include "audio/AudioSensor.h"
#include "audio/AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class RippleReflections : public Fx {
    private:
        Interval int1, int2, int3;
        double t1, t2, t3;

    public:
        RippleReflections(Strip *strip, AudioChannel *audioChannel, State *state);
        void beforeRender();
        CRGB render(int16_t index, double x);
};

#endif
