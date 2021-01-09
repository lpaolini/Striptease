#ifndef Volcane_h
#define Volcane_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioChannel.h"
#include "Fx.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Strip.h"

class Volcane: public Fx {
    private:
        static const int NUM_ITEMS = 10;
        struct Item {
            HarmonicMotion *head = new HarmonicMotion();
            HarmonicMotion *tail = new HarmonicMotion();
        };
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Green);
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        Item *items[NUM_ITEMS];
        void restart(Item *item);

    public:
        Volcane(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
