#ifndef Jelly_h
#define Jelly_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Timer.h"

class Jelly : public Fx {
    private:
        // const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Red, CRGB::White, CRGB::Aqua);
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        const CRGB BACKGROUND_COLOR = CHSV(180, 255, 30);
        static const uint8_t ITEMS = 5;
        static const uint8_t FADE_RATE = 100;
        AudioTrigger *audioTrigger;
        HarmonicMotion items[ITEMS];
        Timer moveTimer = Timer(100, true);
        Timer fadeTimer = Timer(10, true);

    public:
        Jelly(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Jelly();
        void loop();
        void reset();
};

#endif
