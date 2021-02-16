#ifndef Blackout_h
#define Blackout_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Strip.h"

class Blackout: public Fx {
    public:
        Blackout(Strip *strip);
        void loop();
        void reset();
};

#endif
