#ifndef SineMeter_h
#define SineMeter_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioChannel.h"
#include "Fx.h"
#include "Pixel.h"
#include "State.h"

class SineMeter : public Fx {
    private:
        // const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Red);
        Pixel pixel;
        // uint8_t freq = 20;
        uint8_t fade = 1;                                     // How quickly does it fade? Lower = slower fade rate.
        elapsedMillis fadeTimer;

    public:
        SineMeter(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
