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

        uint16_t limitToRange(int16_t index) {
            return max(min(index, last()), first());
        }

    protected:
        bool crop(int16_t &indexFrom, int16_t &indexTo) {
            enforceOrder(indexFrom, indexTo);
            if (indexTo < first() || indexFrom > last()) {
                return false;
            }
            indexFrom = limitToRange(indexFrom);
            indexTo = limitToRange(indexTo);
            return true;
        }

    public:
        bool isInRange(int16_t index) {
            return index >= first() && index <= last();
        }

        uint16_t first() {
            return 0;
        }

        uint16_t center() {
            return size() / 2;
        };

        uint16_t last() {
            return size() - 1;
        }

        uint16_t random() {
            return random16(last());
        }

        uint16_t randomExclude(int16_t excludeIndex, int16_t excludeCount = 0) {
            return (excludeIndex + excludeCount + random16(last() - 2 * excludeCount)) % size();
        }

        uint16_t randomInRange(double from, double to) {
            return random16(from * last(), to * last());
        }

        uint16_t fromNormalizedPosition(double normalizedPosition, int16_t excludeCount = 0) {
            return int(normalizedPosition * (last() - excludeCount));
        }
        
        void rainbow(uint8_t initialHue) {
            rainbow(initialHue, first(), last());
        }

        void rainbow(uint8_t initialHue, uint8_t deltaHue) {
            rainbow(initialHue, deltaHue, first(), last());
        }

        void rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo) {
            uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
            rainbow(initialHue, deltaHue, indexFrom, indexTo);
        }

        void fade(uint8_t amount) {
            fade(amount, first(), last());
        }

        void blur(uint8_t amount) {
            blur(amount, first(), last());
        }

        CRGB shiftUp(CRGB in = CRGB::Black) {
            return shiftUp(first(), last(), in);
        }

        CRGB shiftDown(CRGB in = CRGB::Black) {
            return shiftDown(first(), last(), in);
        }
        
        bool paintNormalized(double position, CRGB color, bool add = true) {
            return paint(fromNormalizedPosition(position), fromNormalizedPosition(position), color, add);
        }

        bool paintRandomPos(int16_t length, CRGB color, bool add = true) {
            uint16_t pos = random16(last() - length);
            return paint(pos, pos + length, color, add);
        }

        bool paintNormalized(double positionFrom, double positionTo, CRGB color, bool add = true) {
            return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
        }

        CRGB getPosition(double position) {
            return getIndex(fromNormalizedPosition(position));
        }

        virtual Strip *buffered(uint8_t opacity = 255) {
            return this;
        }

        virtual void flush() {};
        
        virtual uint16_t size() =0;
        virtual void off() =0;
        virtual void rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) =0;
        virtual void fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) =0;
        virtual void blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) =0;
        virtual CRGB shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual CRGB shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual void paint(CRGB color, bool add = false) =0;
        virtual bool paint(int16_t index, CRGB color, bool add = true) =0;
        virtual bool paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add = true) =0;
        virtual bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add = true) =0;
        virtual CRGB getIndex(int16_t index) =0;
};

#endif
