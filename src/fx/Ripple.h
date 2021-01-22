#ifndef Ripple_h
#define Ripple_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
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
        const CRGB BACKGROUND_COLOR = CHSV(180, 255, 30);
        static const uint8_t ITEMS = 10;
        static const unsigned int DECAY_DELAY = 500;
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        Item *items;
        Timer fadeTimer = Timer(10);
        void loopItem(Item &item, bool &trigger, float strength);
        void fadeItem(Item &item);
        void randomizeItem(Item &item, float strength);

    public:
        Ripple(Strip *strip);
        Ripple(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Ripple();
        void loop();
        void reset();
};

#endif
