#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "Fx.h"
#include "State.h"
#include "Timer.h"

class Matrix : public Fx {
    private:
        const CRGB DOWN_COLOR = CRGB::Green;
        const CRGB UP_COLOR = CRGB::Blue;
        static const unsigned int UP_PERIOD = 2;
        static const unsigned int DOWN_PERIOD = 4;
        AudioTrigger *audioTrigger;
        bool *down;
        bool *up;
        uint16_t countUp;
        uint16_t countDown;
        void addFromTop();
        void addFromBottom();
        void show();

    public:
        Matrix(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Matrix();
        void loop();
        void reset();
};

#endif
