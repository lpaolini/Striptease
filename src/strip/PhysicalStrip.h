#ifndef PhysicalStrip_h
#define PhysicalStrip_h

#include <FastLED.h>
#include "Strip.h"
#include "BufferedStrip.h"
#include "StatefulStrip.h"

template<uint16_t SIZE, uint8_t PIN, uint16_t DENSITY>
class PhysicalStrip : public StatefulStrip {
    private:
        CRGBArray<SIZE> array;

    public:
        PhysicalStrip() : StatefulStrip(array, DENSITY) {
            FastLED.addLeds<WS2812SERIAL, PIN, BRG>(array, SIZE);
        }

        Strip *overlay(uint8_t opacity) {
            return new BufferedStrip(this, opacity);
        }
};

#endif
