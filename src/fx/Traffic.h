#ifndef Traffic_h
#define Traffic_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "audio/AudioSensor.h"
#include "audio/AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"

class Traffic : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Gold, CRGB::Red, CRGB::Blue, CRGB::Teal);
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
