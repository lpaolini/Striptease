#ifndef Ants_h
#define Ants_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "HarmonicMotion.h"
#include "State.h"

class Ants : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        static const uint8_t ITEMS = 10;
        struct Item {
            HarmonicMotion item;
            uint8_t decay;
        };
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        Item *items;
        void loopItem(Item &item, bool &reset, float strength);
        void randomizeItem(Item &item, float strength);

    public:
        Ants(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Ants();
        void loop();
        void reset();
};

#endif
