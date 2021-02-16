#ifndef Juggle_h
#define Juggle_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Pixel.h"
#include "State.h"

class Juggle : public Fx {
    private:
        static const uint8_t DOTS = 5;
        static const uint8_t HUE_INCREMENT = 40;
        static const uint8_t MIN_BEAT = 1;
        static const uint8_t MAX_BEAT = 15;
        static const uint8_t MIN_FADE_RATE = 1; 
        static const uint8_t MAX_FADE_RATE = 10; 
        Pixel pixel[DOTS];
        elapsedMillis fadeTimer;

    public:
        Juggle(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
