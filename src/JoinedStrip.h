#ifndef JoinedStrip_h
#define JoinedStrip_h

#include "Strip.h"

class JoinedStrip : public Strip {
    private: 
        Strip *strip1, *strip2;
        uint16_t distance;
        CRGB *buffer;
        bool isInRange(int16_t index);
        uint16_t limitToRange(int16_t index);

    public:
        JoinedStrip(Strip *strip, Strip *strip2, uint16_t distance = 0);

        CRGB bufferShiftUp(CRGB in);
        CRGB bufferShiftDown(CRGB in);
        
        uint16_t size();
        uint16_t first();
        uint16_t center();
        uint16_t last();
        uint16_t random();
        uint16_t randomExclude(uint16_t excludeIndex, uint16_t excludeCount = 0);
        uint16_t randomInRange(float from, float to);
        uint16_t fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount = 0);

        void off();
        void rainbow(uint8_t initialHue);
        void rainbow(uint8_t initialHue, uint8_t deltaHue);
        void fade(uint8_t amount);
        void blur(uint8_t amount);
        CRGB shiftUp(CRGB in = CRGB::Black);
        CRGB shiftDown(CRGB in = CRGB::Black);
        void paint(CRGB color, bool add = false);
        bool paint(int16_t index, CRGB color, bool add = true);
        bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        bool paintNormalized(float position, CRGB color, bool add = true);
        bool paintNormalized(float positionFrom, float positionTo, CRGB color, bool add = true);
        bool paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add = true);
        bool paintRandomPos(uint16_t length, CRGB color, bool add = true);
};

#endif
