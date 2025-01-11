#ifndef Sunset_h
#define Sunset_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "HarmonicMotion.h"
#include "Gradient.h"

class Sunset : public Fx {
    private:
        Gradient *GRADIENT = new Gradient(CRGB::Blue, CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        HarmonicMotion item;

    public:
        Sunset(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
