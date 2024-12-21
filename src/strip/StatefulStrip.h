#ifndef StatefulStrip_h
#define StatefulStrip_h

#include "Strip.h"

class StatefulStrip : public Strip {
    private: 
        CRGBSet *leds;
        uint16_t density;

    public:
        StatefulStrip(CRGBSet &leds, uint16_t density = 0);
        StatefulStrip(CRGBSet *leds, uint16_t density = 0);
        StatefulStrip();
        void setLeds(CRGBSet *leds);
        uint16_t size() override;
        void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) override;
        void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) override;
        void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) override;
        CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true) override;
        bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add = true) override;
        CRGB getIndex(int16_t index) override;
};

#endif
