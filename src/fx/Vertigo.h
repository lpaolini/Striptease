#ifndef Vertigo_h
#define Vertigo_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"
#include "Timer.h"

class Vertigo : public Fx {
    private:
        static const uint8_t ITEMS = 5;
        static const uint8_t FADE_RATE = 50;
        static const uint16_t INHIBIT_DELAY = 250;
        struct Item {
            HarmonicMotion ball;
            elapsedMillis timer;
        };
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        uint8_t nextItem = 0;
        Timer fadeTimer = Timer(10);
        Timer inhibitTimer = Timer(INHIBIT_DELAY);
        void randomizeItem(Item &item, float strength);

    public:
        Vertigo(Strip *strip, AudioChannel *audioChannel, State *state);
        ~Vertigo();
        void loop();
        void reset();
};

#endif
