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
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Purple, CRGB::Red, CRGB::Yellow);
        elapsedMillis shiftTimer;

    public:
        Scroller(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
