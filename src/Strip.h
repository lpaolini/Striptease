#ifndef Strip_h
#define Strip_h

#include <FastLED.h>

class Strip {
    private:
        void enforceOrder(int16_t &indexFrom, int16_t &indexTo) {
            int16_t from = indexFrom;
            int16_t to = indexTo;
            if (from > to) {
                indexFrom = to;
                indexTo = from;
            }
        }

    public:
        virtual Strip *buffered() {
            return this;
        }

        virtual void flush() {
            // no-op
        };
        
        bool crop(int16_t &indexFrom, int16_t &indexTo) {
            enforceOrder(indexFrom, indexTo);
            if (indexTo < first() || indexFrom > last()) {
                return false;
            }
            indexFrom = limitToRange(indexFrom);
            indexTo = limitToRange(indexTo);
            return true;
        }

        virtual bool isInRange(int16_t index);
        virtual uint16_t limitToRange(int16_t index);
        virtual uint16_t size();
        virtual uint16_t first();
        virtual uint16_t center();
        virtual uint16_t last();
        virtual uint16_t random();
        virtual uint16_t randomExclude(int16_t excludeIndex, int16_t excludeCount = 0);
        virtual uint16_t randomInRange(double from, double to);
        virtual uint16_t fromNormalizedPosition(double normalizedPosition, int16_t excludeCount = 0);
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
        virtual bool paintNormalized(double position, CRGB color, bool add = true);
        virtual bool paintNormalized(double positionFrom, double positionTo, CRGB color, bool add = true);
        virtual bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add = true);
        virtual bool paintRandomPos(int16_t length, CRGB color, bool add = true);
        virtual CRGB getIndex(int16_t index);
        virtual CRGB getPosition(double pos);
};

#endif
