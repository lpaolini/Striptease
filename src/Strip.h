#ifndef Strip_h
#define Strip_h

#include <FastLED.h>

class Strip {
  public:
    CRGBSet *leds;
    uint16_t count;
    float length;
    
    Strip(CRGBSet &leds, uint16_t density);
    void off();
    void fill(CRGB color);
    void fullRainbow(uint8_t initialHue);
    void fade(uint8_t amount);
    uint16_t toPosition(float x);
    uint16_t toNormalizedPosition(float x, uint16_t excludeCount = 0);
    bool isInRange(int16_t position);
    uint16_t limitToRange(int16_t position);
    void shiftUp();
    void shiftDown();
    uint16_t randomPos(uint16_t excludeCount = 0);
    uint16_t randomPosRange(float from, float to);
    uint16_t randomPosExclude(uint16_t excludePosition, uint16_t excludeCount);
    uint16_t centerPos();
    uint16_t lastPos();
    bool paint(int16_t from, int16_t to, CRGB color, bool add = true);
    bool paintNormalized(float from, float to, CRGB color, bool add = true);
    bool paintNormalizedSize(float from, uint16_t size, CRGB color, bool add = true);
    bool paintRandomPos(uint16_t size, CRGB color, bool add = true);
};

#endif
