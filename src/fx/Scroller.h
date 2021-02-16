#ifndef Scroller_h
#define Scroller_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioChannel.h"
#include "Fx.h"
#include "Pixel.h"
#include "State.h"

class Scroller : public Fx {
    private:
        // const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Aqua, CRGB::White, CRGB::Red);
        elapsedMillis shiftTimer;

    public:
        Scroller(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
