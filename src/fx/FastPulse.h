#ifndef FastPulse_h
#define FastPulse_h

#include <Arduino.h>
#include <FastLED.h>
#include "audio/AudioSensor.h"
#include "audio/AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class FastPulse : public Fx {
    private:
        Interval int1;
        double t1;
        CRGB pulseColor;

    public:
        FastPulse(Strip *strip, AudioChannel *audioChannel, State *state, CRGB pulseColor = CRGB::White);
        void beforeRender();
        CRGB render(int16_t index, double x);
};

#endif
