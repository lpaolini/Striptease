#ifndef Background_h
#define Background_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Strip.h"

class Background: public Fx {
    private:
        CRGB color;

    public:
        Background(Strip *strip, CRGB color = CRGB::Black);
        void loop();
        void reset();
};

#endif
