#ifndef RippleReflections_h
#define RippleReflections_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class RippleReflections : public Fx {
    private:
        Interval int1;
        Interval int2;
        Interval int3;

    public:
        RippleReflections(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
