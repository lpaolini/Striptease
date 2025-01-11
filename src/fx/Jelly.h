#ifndef Jelly_h
#define Jelly_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "Gradient.h"
#include "Timer.h"

class Jelly : public Fx {
    private:
        Gradient GRADIENT = Gradient(CRGB::Red, CRGB::Gold, CRGB::Red, CRGB::Blue);
        static const uint8_t HALF_SIZE = 3;
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
