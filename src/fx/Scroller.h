/**
 * Thanks to Ben Rolling for inspiring this effect (color based on dominant frequency), and for the awesome palette!
 * Thanks to Antonio Petti for providing a great idea (instantaneous slow down on beat)!
 **/

#ifndef Scroller_h
#define Scroller_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioChannel.h"
#include "AudioTrigger.h"
#include "Easing.h"
#include "Fx.h"
#include "Pixel.h"
#include "State.h"

class Scroller : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Purple, CRGB::Red, CRGB::Yellow);
        elapsedMillis shiftTimer;
        bool slowDown = false;
        AudioTrigger *audioTrigger;

    public:
        Scroller(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
