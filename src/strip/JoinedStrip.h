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
        void off();
        void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo);
        void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        void paint(CRGB color, bool add = false);
        bool paint(int16_t index, CRGB color, bool add = true);
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        bool paintNormalized(double positionFrom, double positionTo, CRGB color, bool add = true);
        bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add = true);
        bool paintRandomPos(int16_t length, CRGB color, bool add = true);
        CRGB getIndex(int16_t index);
        CRGB getPosition(double pos);
};

#endif
