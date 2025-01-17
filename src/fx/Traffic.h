#ifndef Traffic_h
#define Traffic_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "Gradient.h"
#include "HarmonicMotion.h"

class Traffic : public Fx {
    private:
        Gradient GRADIENT = Gradient(CRGB::Gold, CRGB::Red, CRGB::Blue, CRGB::Teal);
        static const uint8_t LAYERS = 10;
        static const uint8_t ITEMS = 100;
        AudioTrigger *audioTrigger;
        HarmonicMotion *items;
        void loopItem(HarmonicMotion &item, bool &trigger);
        void resetItem(HarmonicMotion &item);

    public:
        Traffic(Strip *strip, AudioChannel *audioChannel, State *stateAUpd);
        ~Traffic();
        void loop();
        void reset();
};

#endif
