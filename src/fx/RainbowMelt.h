#ifndef RainbowMelt_h
#define RainbowMelt_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class RainbowMelt : public Fx {
    private:
        Interval int1;

    public:
        RainbowMelt(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
