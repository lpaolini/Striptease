#ifndef Blur_h
#define Blur_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"

class Blur : public Fx {
    public:
        Blur(Strip *strip);
        void loop();
        void reset();
};

#endif
