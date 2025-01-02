#ifndef RainbowMelt_h
#define RainbowMelt_h

#include <Arduino.h>
#include <FastLED.h>
#include "audio/AudioSensor.h"
#include "audio/AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class RainbowMelt : public Fx {
    private:
        Interval int1;
        double t1;

    public:
        RainbowMelt(Strip *strip, AudioChannel *audioChannel, State *state);
        void beforeRender();
        CRGB render(int16_t index, double x);
};

#endif
