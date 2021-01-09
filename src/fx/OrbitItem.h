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
        static constexpr float MIN_SPEED = 50;
        static constexpr float SPEED_FACTOR = 300;
        Strip *strip;
        State *state;
        uint8_t hue;
        float phase; // degrees
        float speed; // degrees per second
        float eccentricity;
        float eccentricityAngle;
        Pixel pixel;
        elapsedMicros timeElapsed;
        float angle;

    public:
        OrbitItem();
        void setup(
            Strip *strip,
            State *state,
            uint8_t hue,
            float phase,
            float speed,
            float eccentricity = 0,
            float eccentricityAngle = 0
        );
        void reset();
        void loop();
};

#endif
