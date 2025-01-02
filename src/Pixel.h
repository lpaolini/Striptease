#ifndef Pixel_h
#define Pixel_h

#include <Arduino.h>
#include <FastLED.h>
#include "strip/Strip.h"

class Pixel {
    private:
        Strip *strip;
        bool first;
        int pos0;

    public:
        Pixel();
        void setup(Strip *strip);
        void reset();
        bool set(int pos, CRGB color, bool add = true);
        bool setNormalized(double pos, CRGB color);
};

#endif
