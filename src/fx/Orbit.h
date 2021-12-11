#ifndef Orbit_h
#define Orbit_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Pixel.h"
#include "State.h"
#include "Timer.h"
#include "OrbitItem.h"

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
