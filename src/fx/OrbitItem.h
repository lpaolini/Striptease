#ifndef OrbitItem_h
#define OrbitItem_h

#include <Arduino.h>
#include <FastLED.h>
#include "Strip.h"
#include "Pixel.h"
#include "State.h"

class OrbitItem {
    private:
        static const uint8_t MIN_BRIGHTNESS = 75;
        static constexpr double MIN_SPEED = 50;
        static constexpr double SPEED_FACTOR = 300;
        Strip *strip;
        State *state;
        uint8_t hue;
        double phase; // degrees
        double speed; // degrees per second
        double eccentricity;
        double eccentricityAngle;
        Pixel pixel;
        elapsedMicros timeElapsed;
        double angle;

    public:
        OrbitItem();
        void setup(
            Strip *strip,
            State *state,
            uint8_t hue,
            double phase,
            double speed,
            double eccentricity = 0,
            double eccentricityAngle = 0
        );
        void reset();
        void loop();
};

#endif
