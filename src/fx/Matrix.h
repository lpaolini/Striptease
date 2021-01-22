#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Timer.h"

class Matrix : public Fx {
    private:
        const CRGB DOWN_COLOR = CRGB::Green;
        const CRGB UP_COLOR = CRGB::Blue;
        static const unsigned int INTERVAL = 12;
        static const unsigned int DOWN_INTERVAL = INTERVAL * 2;
        static const unsigned int DOWN_PROBABILITY = 10;
        static const unsigned int UP_INTERVAL = INTERVAL * 1;
        static const unsigned int UP_PROBABILITY = 2;
        Strip *strip;
        AudioChannel *audioChannel;
        bool trigger;
        bool *down;
        bool *up;
        void show();
        Timer downInterval = Timer(DOWN_INTERVAL);
        Timer upInterval = Timer(UP_INTERVAL);

    public:
        Matrix(Strip *strip, AudioChannel *audioChannel);
        ~Matrix();
        void loop();
        void reset();
};

#endif
