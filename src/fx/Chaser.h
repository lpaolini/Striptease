#ifndef Chaser_h
#define Chaser_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Timer.h"

class Chaser : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Red, CRGB::White, CRGB::Aqua);
        const CRGB BACKGROUND_COLOR = CHSV(180, 255, 30);
        static const uint8_t ITEMS = 5;
        static const uint8_t FADE_RATE = 100;
        AudioTrigger *audioTrigger;
        HarmonicMotion items[ITEMS];
        Timer moveTimer = Timer(100, true);
        Timer fadeTimer = Timer(10, true);

    public:
        Chaser(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Chaser();
        void loop();
        void reset();
};

#endif
