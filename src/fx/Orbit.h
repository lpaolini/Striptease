#ifndef Orbit_h
#define Orbit_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Pixel.h"
#include "State.h"
#include "Timer.h"
#include "OrbitItem.h"

class Orbit : public Fx {
    private:
        // static const uint8_t ITEMS = 2;
        // static const uint8_t HUE_STEP = 160;
        // static constexpr float ANGLE_STEP = -180;
        // static constexpr float SPEED_STEP = 0;
        // static constexpr float ECCENTRICITY = .2;
        // static constexpr float ECCENTRICITY_ANGLE = 270;
        static const uint8_t ITEMS = 10;
        static const uint8_t HUE_STEP = 20;
        static constexpr float ANGLE_STEP = -10;
        static constexpr float SPEED_STEP = 0;
        static constexpr float ECCENTRICITY = .2;
        static constexpr float ECCENTRICITY_ANGLE = 270;
        float phase;
        OrbitItem item[ITEMS];
        Timer timer = Timer(5);

    public:
        Orbit(Strip *strip, State *state, float phase = 0);
        void loop();
        void reset();
};

#endif
