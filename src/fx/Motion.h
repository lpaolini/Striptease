#ifndef Motion_h
#define Motion_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Timer.h"

class Motion : public Fx {
    private:
        static const uint8_t ITEMS = 5;
        static const uint8_t FADE_RATE = 200;
        static const uint16_t INHIBIT_TIME_MS = 100;
        struct Item {
            HarmonicMotion ball;
        };
        CRGB color;
        double velocityFactor;
        double accelerationFactor;
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        uint8_t nextItem = 0;
        Timer fadeTimer = Timer(10);
        Timer inhibitTimer = Timer(INHIBIT_TIME_MS);
        void resetItem(Item &item);

    public:
        Motion(Strip *strip, AudioChannel *audioChannel, State *state, CRGB color = CRGB::Blue, double velocityFactor = 100, double accelerationFactor = 100);
        ~Motion();
        void loop();
        void reset();
};

#endif
