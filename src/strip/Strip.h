#ifndef Strip_h
#define Strip_h

#include <FastLED.h>

class Strip {
    private:
        static void enforceOrder(int16_t &indexFrom, int16_t &indexTo) {
            int16_t from = indexFrom;
            int16_t to = indexTo;
            if (from > to) {
                indexFrom = to;
                indexTo = from;
            }
        }

        static double clamp16(double value) {
            const double clampedDown = value < INT16_MIN ? INT16_MIN : value;
            const double clampedUp = clampedDown > INT16_MAX ? INT16_MAX : clampedDown;
            return round(clampedUp);
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

        virtual void _rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) =0;
        virtual void _fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) =0;
        virtual void _blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) =0;
        virtual CRGB _shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual CRGB _shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual bool _paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) =0;

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

        uint16_t fromNormalizedPosition(double normPos, int16_t excludeCount = 0) {
            return clamp16(first() + normPos * (last() - excludeCount));
        }
        
        void off() {
            _paint(first(), last(), CRGB::Black, false);
        }

        void rainbow(uint8_t initialHue) {
            uint8_t deltaHue = max(255 / size(), 1);
            _rainbow(initialHue, deltaHue, first(), last());
        }

        void rainbow(uint8_t initialHue, uint8_t deltaHue) {
            _rainbow(initialHue, deltaHue, first(), last());
        }

        void rainbow(uint8_t initialHue, double posFrom, double posTo) {
            uint16_t indexFrom = clamp16(posFrom);
            uint16_t indexTo = clamp16(posTo);
            uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
            _rainbow(initialHue, deltaHue, indexFrom, indexTo);
        }

        void rainbow(uint8_t initialHue, uint8_t deltaHue, double posFrom, double posTo) {
            uint16_t indexFrom = clamp16(posFrom);
            uint16_t indexTo = clamp16(posTo);
            _rainbow(initialHue, deltaHue, indexFrom, indexTo);
        }

        void fade(uint8_t amount) {
            _fade(amount, first(), last());
        }

        void fade(uint8_t amount, double posFrom, double posTo) {
            _fade(amount, clamp16(posFrom), clamp16(posTo));
        }

        void blur(uint8_t amount) {
            _blur(amount, first(), last());
        }

        void blur(uint8_t amount, double posFrom, double posTo) {
            _blur(amount, clamp16(posFrom), clamp16(posTo));
        }

        CRGB shiftUp(CRGB in = CRGB::Black) {
            return _shiftUp(first(), last(), in);
        }

        CRGB shiftUp(double posFrom, double posTo, CRGB in = CRGB::Black) {
            return _shiftUp(clamp16(posFrom), clamp16(posTo), in);
        }

        CRGB shiftDown(CRGB in = CRGB::Black) {
            return _shiftDown(first(), last(), in);
        }
        
        CRGB shiftDown(double posFrom, double posTo, CRGB in = CRGB::Black) {
            return _shiftDown(clamp16(posFrom), clamp16(posTo), in);
        }
        
        void paint(CRGB color, bool add) {
            _paint(first(), last(), color, add);
        }

        void paint(CHSV color, bool add) {
            CRGB rgb;
            hsv2rgb_rainbow(color, rgb);
            _paint(first(), last(), rgb, add);
        }

        bool paint(double pos, CRGB color, bool add) {
            return _paint(clamp16(pos), clamp16(pos), color, add);
        }

        bool paint(double posFrom, double posTo, CRGB color, bool add) {
            return _paint(clamp16(posFrom), clamp16(posTo), color, add);
        }

        bool paintNormalized(double normPos, CRGB color, bool add) {
            return _paint(fromNormalizedPosition(normPos), fromNormalizedPosition(normPos), color, add);
        }

        bool paintNormalized(double normPosFrom, double norPosTo, CRGB color, bool add) {
            return _paint(fromNormalizedPosition(normPosFrom), fromNormalizedPosition(norPosTo), color, add);
        }

        bool paintRandomPos(int16_t length, CRGB color, bool add) {
            uint16_t pos = random16(size() - length);
            return _paint(pos, pos + length, color, add);
        }

        CRGB getPosition(double normPos) {
            return getIndex(fromNormalizedPosition(normPos));
        }

        virtual void flush() {};        
        virtual Strip *overlay(double opacity = 1) =0;
        virtual uint16_t size() =0;
        virtual bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) =0;
        virtual CRGB getIndex(int16_t index) =0;
};

#endif
