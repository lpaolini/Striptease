#ifndef Bounce_h
#define Bounce_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"

class Bounce : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        static const uint16_t COUNT = 2;
        static const uint16_t SIZE = 10;
        uint16_t count;
        uint16_t size;
        HarmonicMotion *items;
        void loopItem(HarmonicMotion &item);
        void resetItem(HarmonicMotion &item);

    public:
        Bounce(Strip *strip, State *state, uint16_t count = COUNT, uint16_t size = SIZE);
        ~Bounce();
        void loop();
        void reset();
};

#endif
