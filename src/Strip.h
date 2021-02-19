#ifndef Strip_h
#define Strip_h

#include <FastLED.h>

class Strip {
    public:
        virtual 
        Strip *buffered() {
            return this;
        }
        void sanitize(int16_t &indexFrom, int16_t &indexTo) {
            int16_t from = limitToRange(indexFrom);
            int16_t to = limitToRange(indexTo);
            if (from <= to) {
                indexFrom = from;
                indexTo = to;
            } else {
                indexFrom = to;
                indexTo = from;
            }
        }
        virtual void flush() {};
        virtual bool isInRange(int16_t index);
        virtual uint16_t limitToRange(int16_t index);
        virtual uint16_t size();
        virtual uint16_t first();
        virtual uint16_t center();
        virtual uint16_t last();
        virtual uint16_t random();
        virtual uint16_t randomExclude(int16_t excludeIndex, int16_t excludeCount = 0);
        virtual uint16_t randomInRange(float from, float to);
        virtual uint16_t fromNormalizedPosition(float normalizedPosition, int16_t excludeCount = 0);
        virtual void off();
        virtual void rainbow(uint8_t initialHue);
        virtual void rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo);
        virtual void rainbow(uint8_t initialHue, uint8_t deltaHue);
        virtual void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo);
        virtual void fade(uint8_t amount);
        virtual void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        virtual void blur(uint8_t amount);
        virtual void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo);
        virtual CRGB shiftUp(CRGB in = CRGB::Black);
        virtual CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        virtual CRGB shiftDown(CRGB in = CRGB::Black);
        virtual CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black);
        virtual void paint(CRGB color, bool add = false);
        virtual bool paint(int16_t index, CRGB color, bool add = true);
        virtual bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true);
        virtual bool paintNormalized(float position, CRGB color, bool add = true);
        virtual bool paintNormalized(float positionFrom, float positionTo, CRGB color, bool add = true);
        virtual bool paintNormalizedSize(float positionFrom, int16_t size, CRGB color, bool add = true);
        virtual bool paintRandomPos(int16_t length, CRGB color, bool add = true);
};

#endif
