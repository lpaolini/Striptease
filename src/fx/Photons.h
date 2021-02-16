#ifndef Photons_h
#define Photons_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "Fx.h"
#include "HarmonicMotion.h"
#include "State.h"

class Photons: public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::White, CRGB::Aqua, CRGB::Red, CRGB::Blue);
        static constexpr float MIN_SPEED = 100;
        static constexpr float MAX_SPEED = 1000;
        static const uint8_t NUM_PHOTONS = 10;
        static const uint8_t MAX_CONCURRENT = 3;
        AudioTrigger *audioTrigger;
        HarmonicMotion items[NUM_PHOTONS];
        
    public:
        Photons(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Photons();
        void resetItem(HarmonicMotion &item);
        void reset();
        void loop();
};

#endif
