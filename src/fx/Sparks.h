#ifndef Sparks_h
#define Sparks_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "Timer.h"

class Sparks : public Fx {
    private:
        const CRGB BACKGROUND_COLOR = CRGB::Black;
        static const uint8_t ITEMS = 3;
        static const uint16_t HOLD_OFF_TIME_MS = 100;
        struct Item {
            HarmonicMotion center;
            HarmonicMotion sides;
        };
        CRGB centerColor;
        CRGB sidesColor;
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        uint8_t nextItem = 0;
        Timer holdOffTimer = Timer(HOLD_OFF_TIME_MS);
        void loopItem(Item &item, bool &trigger, double strength);
        void randomizeItem(Item &item, double strength);

    public:
        Sparks(Strip *strip, AudioChannel *audioChannel, State *state, CRGB centerColor = CRGB::DarkOrange, CRGB sidesColor = CRGB::Blue);
        ~Sparks();
        void loop();
        void reset();
};

#endif
