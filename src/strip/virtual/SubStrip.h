#ifndef SubStrip_h
#define SubStrip_h

#include <FastLED.h>
#include "strip/Strip.h"
#include "strip/BufferedStrip.h"

class SubStrip : public Strip {
    private: 
        Strip *strip;
        uint16_t start;
        uint16_t end;
        int16_t toStrip(int16_t index);

    public:
        SubStrip(Strip *strip, int16_t start, int16_t end);
        Strip *overlay(double opacity = 1) override;
        uint16_t size() override;
        void _fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) override;
        void _blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) override;
        CRGB _shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        CRGB _shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        bool _paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool overlay) override;
        bool _paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool overlay) override;
        bool _paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) override;
        bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool overlay) override;
        CRGB getIndex(int16_t index) override;
};

#endif
