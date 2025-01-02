#ifndef Orbit_h
#define Orbit_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Pixel.h"
#include "Timer.h"
#include "Pixel.h"

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

class Orbit : public Fx {
    private:
        // static const uint8_t ITEMS = 2;
        // static const uint8_t HUE_STEP = 160;
        // static constexpr double ANGLE_STEP = -180;
        // static constexpr double SPEED_STEP = 0;
        // static constexpr double ECCENTRICITY = .2;
        // static constexpr double ECCENTRICITY_ANGLE = 270;
        static const uint8_t ITEMS = 10;
        static const uint8_t HUE_STEP = 20;
        static constexpr double ANGLE_STEP = -10;
        static constexpr double SPEED_STEP = 0;
        static constexpr double ECCENTRICITY = .2;
        static constexpr double ECCENTRICITY_ANGLE = 270;
        double phase;
        OrbitItem item[ITEMS];
        Timer timer = Timer(5);

    public:
        Orbit(Strip *strip, State *state, double phase = 0);
        void loop();
        void reset();
};

#endif
