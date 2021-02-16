#ifndef Glitter_h
#define Glitter_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "State.h"
#include "Timer.h"

class Glitter : public Fx {
    private:
        static const uint8_t SEGMENT_LENGTH = 10;
        static const uint8_t FADE_RATE = 30;
        Timer timer = Timer(0, true);
        Timer fadeTimer = Timer(10, true);

    public:
        Glitter(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
