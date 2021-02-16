#ifndef Fireworks_h
#define Fireworks_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Timer.h"

class Fireworks : public Fx {
    private:
        // const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Red, CRGB::Gold);
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        static const uint8_t ITEMS = 4;
        static const uint8_t FADE_RATE = 5;
        static const uint16_t DECAY_RATE = 5;
        static const uint16_t DECAY_DELAY = 500;
        static const uint16_t INHIBIT_DELAY = 250;
        struct Item {
            HarmonicMotion ball;
            elapsedMillis timer;
            uint8_t decay;
        };
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        uint8_t nextItem = 0;
        Timer fadeTimer = Timer(10);
        Timer inhibitTimer = Timer(INHIBIT_DELAY);
        void randomizeItem(Item &item, float strength);

    public:
        Fireworks(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Fireworks();
        void loop();
        void reset();
};

#endif
