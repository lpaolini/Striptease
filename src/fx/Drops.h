#ifndef Drops_h
#define Drops_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"

class Drops : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::HotPink, CRGB::Blue, CRGB::Aqua, CRGB::Fuchsia);
        const CRGB BACKGROUND_COLOR = CRGB::Black;
        // const CRGB BACKGROUND_COLOR = CHSV(180, 255, 30);
        static const uint8_t ITEMS = 5;
        struct Item {
            HarmonicMotion center;
            HarmonicMotion sides;
            uint8_t decay;
        };
        AudioTrigger *audioTrigger;
        Item *items;
        void loopItem(Item &item, bool &trigger, double strength);
        void randomizeItem(Item &item, double strength);

    public:
        Drops(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Drops();
        void loop();
        void reset();
};

#endif
