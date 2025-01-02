#ifndef Ripple_h
#define Ripple_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"

class Ripple : public Fx {
    private:
        struct Item {
            HarmonicMotion ball;
            elapsedMillis timer;
            uint8_t decay;
        };
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::HotPink, CRGB::Blue, CRGB::Aqua, CRGB::Fuchsia);
        static const uint8_t ITEMS = 10;
        static const unsigned int DECAY_DELAY = 500;
        AudioTrigger *audioTrigger;
        Item *items;
        CRGB backgroundColor;
        Timer fadeTimer = Timer(10);
        void loopItem(Item &item, bool &trigger, double strength);
        void fadeItem(Item &item);
        void randomizeItem(Item &item, double strength);

    public:
        Ripple(Strip *strip, AudioChannel *audioChannel, State *state, CRGB backgroundColor = CHSV(160, 255, 50));
        ~Ripple();
        void loop();
        void reset();
};

#endif
