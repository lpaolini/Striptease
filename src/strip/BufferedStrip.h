#ifndef BufferedStrip_h
#define BufferedStrip_h

#include <FastLED.h>
#include "Strip.h"
#include "StatefulStrip.h"

class BufferedStrip : public StatefulStrip {
    private:
        Strip *strip;
        double opacity;

    public:
        BufferedStrip(Strip *strip, double opacity) : StatefulStrip(new CRGBSet(new CRGB[strip->size()], strip->size())) {
            this->strip = strip;
            this->opacity = max(0L, min(1L, opacity));
        }

        void flush() override {
            for (uint16_t i = 0; i < strip->size(); i++) {
                strip->paint(i, (*leds)[i].scale8((uint8_t)(255 * opacity)), true);
            }
        }
};

#endif
