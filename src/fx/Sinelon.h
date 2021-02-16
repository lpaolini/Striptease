#ifndef Sinelon_h
#define Sinelon_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Pixel.h"
#include "State.h"

class Sinelon : public Fx {
    private:
        // const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Aqua, CRGB::White);
        Pixel pixel1, pixel2, pixel3, pixel4;
        uint8_t freq1 = 11;
        uint8_t freq2 = 17;
        uint8_t freq3 = 23;
        // uint8_t freq1 = 33;
        // uint8_t freq2 = 38;
        // uint8_t freq3 = 41;
        uint8_t fade = 10;                                     // How quickly does it fade? Lower = slower fade rate.

    public:
        Sinelon(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
