#ifndef Volcane_h
#define Volcane_h

#include <Arduino.h>
#include <FastLED.h>
#include "audio/AudioTrigger.h"
#include "Fx.h"
#include "HarmonicMotion.h"

class Volcane: public Fx {
    private:
        static const int NUM_ITEMS = 10;
        struct Item {
            HarmonicMotion head;
            HarmonicMotion tail;
        };
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Green);
        AudioTrigger *audioTrigger;
        Item items[NUM_ITEMS];
        void restart(Item *item);

    public:
        Volcane(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Volcane();
        void loop();
        void reset();
};

#endif
