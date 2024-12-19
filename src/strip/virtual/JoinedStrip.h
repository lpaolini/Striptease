#ifndef JoinedStrip_h
#define JoinedStrip_h

#include "Strip.h"
#include "strip/BufferedStrip.h"
#include "strip/StatefulStrip.h"

class JoinedStrip : public Strip {
    private: 
        Strip *strip1, *strip2;
        uint16_t gap;
        StatefulStrip *gapStrip;
        bool isInStrip1(int16_t index);
        bool isInGap(int16_t index);
        bool isInStrip2(int16_t index);
        int16_t toStrip1(int16_t index);
        int16_t toGap(int16_t index);
        int16_t toStrip2(int16_t index);

    public:
        JoinedStrip(Strip *strip, Strip *strip2, int16_t gap = 0);
        Strip *buffered(uint8_t opacity = 255);
        uint16_t size() override;
        void off() override;
        void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) override;
        void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) override;
        void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) override;
        CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        void paint(CRGB color, bool add = false) override;
        bool paint(int16_t index, CRGB color, bool add = true) override;
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true) override;
        bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add = true) override;
        CRGB getIndex(int16_t index) override;
};

#endif
