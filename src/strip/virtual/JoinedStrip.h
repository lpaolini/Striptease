#ifndef JoinedStrip_h
#define JoinedStrip_h

#include <FastLED.h>
#include "strip/Strip.h"
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
        double relativeGradient(int16_t indexFrom, int16_t indexTo, int16_t index, double gradientFrom, double gradientTo);

    public:
        JoinedStrip(Strip *strip, Strip *strip2, int16_t gap = 0);
        Strip *overlay(double opacity = 1) override;
        uint16_t size() override;
        void _fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) override;
        void _blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) override;
        CRGB _shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        CRGB _shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) override;
        bool _paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) override;
        bool _paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool add) override;
        bool _paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) override;
        bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) override;
        CRGB getIndex(int16_t index) override;
};

#endif
