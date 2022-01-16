#ifndef SubtleWave_h
#define SubtleWave_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioChannel.h"
#include "Fx.h"
#include "Interval.h"
#include "Pixel.h"
#include "State.h"

class SubtleWave : public Fx {
    private:
        Interval int1, int2;
        double t1, t2;

    public:
        SubtleWave(Strip *strip, AudioChannel *audioChannel, State *state);
        void beforeRender();
        CRGB render(int16_t index, double x);
};

#endif
