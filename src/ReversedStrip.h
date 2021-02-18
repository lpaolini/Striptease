#ifndef ReversedStrip_h
#define ReversedStrip_h

#include "Strip.h"
#include "BufferedStrip.h"

class ReversedStrip : public Strip {
    private: 
        Strip *strip;

    public:
        ReversedStrip(Strip *strip);
        Strip *buffered();
        uint16_t size();
        uint16_t first();
        uint16_t center();
        uint16_t last();
        bool isInRange(int16_t index);
        uint16_t limitToRange(int16_t index);
        uint16_t random();
        uint16_t randomExclude(uint16_t excludeIndex, uint16_t excludeCount = 0);
        uint16_t randomInRange(float from, float to);
        uint16_t fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount = 0);
        void off();
        void rainbow(uint8_t initialHue);
        void rainbow(uint8_t initialHue, uint8_t deltaHue);
        void rainbow(uint8_t initialHue, uint16_t indexFrom, uint16_t indexTo);
        void rainbow(uint8_t initialHue, uint8_t deltaHue, uint16_t indexFrom, uint16_t indexTo);
        void fade(uint8_t amount);
        void fade(uint8_t amount, uint16_t indexFrom, uint16_t indexTo);
        void blur(uint8_t amount);
        void blur(uint8_t amount, uint16_t indexFrom, uint16_t indexTo);
        CRGB shiftUp(CRGB in = CRGB::Black);
        CRGB shiftUp(uint16_t indexFrom, uint16_t indexTo, CRGB in = CRGB::Black);
        CRGB shiftDown(CRGB in = CRGB::Black);
        CRGB shiftDown(uint16_t indexFrom, uint16_t indexTo, CRGB in = CRGB::Black);
        void paint(CRGB color, bool add = false);
        bool paint(int16_t index, CRGB color, bool add = true);
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        bool paintNormalized(float position, CRGB color, bool add = true);
        bool paintNormalized(float positionFrom, float positionTo, CRGB color, bool add = true);
        bool paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add = true);
        bool paintRandomPos(uint16_t length, CRGB color, bool add = true);
};

#endif
