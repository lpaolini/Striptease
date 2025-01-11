#ifndef Scan_h
#define Scan_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "HarmonicMotion.h"
#include "Gradient.h"

class Scan : public Fx {
    private:
        Gradient *GRADIENT = new Gradient(CRGB::Red, CRGB::Green, CRGB::Blue);
        HarmonicMotion item;

    public:
        Scan(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
