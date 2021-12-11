#ifndef Spiral_h
#define Spiral_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "State.h"
#include "EllipticMotion.h"

class Spiral : public Fx {
    private:
        static constexpr double MIN_ANGULAR_SPEED = 20;
        static constexpr double MAX_ANGULAR_SPEED = 120;
        Timer fadeTimer = Timer(5);
        EllipticMotion *items;
        uint16_t count;
        double turns;
        double eccentricity;

    public:
        Spiral(Strip *strip, State *state, uint16_t count = 10, double turns = 1, double eccentricity = 0);
        void loop();
        void reset();
};

#endif
