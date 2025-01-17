#ifndef Elastic_h
#define Elastic_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "Timer.h"

class Elastic : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::White, CRGB::Blue, CRGB::Aqua, CRGB::Red);
        AudioTrigger *audioTrigger;
        static const uint8_t ITEMS = 3;
        static const uint8_t FADE_RATE = 30;
        HarmonicMotion items[ITEMS];
        uint8_t nextItem = 0;
        Timer fadeTimer = Timer(10);
        void randomizeItem(HarmonicMotion &item, double strength);

    public:
        Elastic(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Elastic();
        void loop();
        void reset();
};

#endif
