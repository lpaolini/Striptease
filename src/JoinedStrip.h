#ifndef JoinedStrip_h
#define JoinedStrip_h

#include "Strip.h"
#include "BufferedStrip.h"
#include "StatefulStrip.h"

class JoinedStrip : public Strip {
    private: 
        Strip *strip1, *strip2;
        uint16_t gap;
        CRGB *buffer;
        CRGBSet *bufferSet;
        StatefulStrip *gapStrip;
        bool isInStrip1(int16_t index);
        bool isInGap(int16_t index);
        bool isInStrip2(int16_t index);
        int16_t toStrip1(int16_t index);
        int16_t toGap(int16_t index);
        int16_t toStrip2(int16_t index);

    public:
        JoinedStrip(Strip *strip, Strip *strip2, int16_t gap = 0);
        Strip *buffered();
        uint16_t size();
        uint16_t first();
        uint16_t center();
        uint16_t last();
        bool isInRange(int16_t index);
        uint16_t limitToRange(int16_t index);
        uint16_t random();
        uint16_t randomExclude(int16_t excludeIndex, int16_t excludeCount = 0);
        uint16_t randomInRange(float from, float to);
        uint16_t fromNormalizedPosition(float normalizedPosition, int16_t excludeCount = 0);
        void off();
        void rainbow(uint8_t initialHue);
        void rainbow(uint8_t initialHue, uint8_t deltaHue);
        void rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo);
        void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo);
        void fade(uint8_t amount);
        void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        void blur(uint8_t amount);
        void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        CRGB shiftUp(CRGB in = CRGB::Black);
        CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        CRGB shiftDown(CRGB in = CRGB::Black);
        CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        void paint(CRGB color, bool add = false);
        bool paint(int16_t index, CRGB color, bool add = true);
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        bool paintNormalized(float position, CRGB color, bool add = true);
        bool paintNormalized(float positionFrom, float positionTo, CRGB color, bool add = true);
        bool paintNormalizedSize(float positionFrom, int16_t size, CRGB color, bool add = true);
        bool paintRandomPos(int16_t length, CRGB color, bool add = true);
};

#endif
