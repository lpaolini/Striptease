#ifndef ReversedStrip_h
#define ReversedStrip_h

#include "Strip.h"
#include "strip/BufferedStrip.h"

class ReversedStrip : public Strip {
    private: 
        Strip *strip;
        int16_t toStrip(int16_t index);

    public:
        ReversedStrip(Strip *strip);
        Strip *buffered();
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
