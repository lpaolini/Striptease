#ifndef Photon_h
#define Photon_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "State.h"
#include "Strip.h"

class Photon {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::White, CRGB::Blue, CRGB::Aqua, CRGB::Red);
        static constexpr float MIN_SPEED = .5f;
        static constexpr float MAX_SPEED = 3.0f;
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        CRGB color;
        bool first = true;
        float x0;
        float v;        // Initial velocity (m/s)
        unsigned long t0;        // Initial time
        // int pos;

    public:
        Photon();
        void setup(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
