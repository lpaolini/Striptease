#ifndef Traffic_h
#define Traffic_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "AudioSensor.h"
#include "AudioTrigger.h"
#include "HarmonicMotion.h"
#include "State.h"

class Traffic : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Gold, CRGB::Red, CRGB::Blue);
        static const uint8_t LAYERS = 5;
        CRGB layerColors[LAYERS];
        static const uint8_t FIXED_COLORS = 4;
        CRGB fixedColors[FIXED_COLORS] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Violet};
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
