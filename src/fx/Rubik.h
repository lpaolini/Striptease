#ifndef Rubik_h
#define Rubik_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Timer.h"

class Rubik : public Fx {
    private:
        Strip *strip;
        uint8_t lightness = 100;
        CHSV colors[6] = { CHSV(0, 255, lightness), CHSV(32, 255, lightness), CHSV(64, 255, lightness), CHSV(96, 255, lightness), CHSV(160, 255, lightness), CHSV(0, 0, lightness) };
        CHSV currentColors[6];
        int angle = 0;
        int step = 200;
        void facet(long start, int len, int index, CRGB color);
        void paint(long start, int len, CRGB color);
        Timer timer = Timer(10);
        void randomize();

    public:
        Rubik(Strip *Strip);
        void loop();
        void reset();
};

#endif
