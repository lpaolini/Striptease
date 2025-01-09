#ifndef Strip_h
#define Strip_h

#include <FastLED.h>
#include "Gradient.h"

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

        virtual void _fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) =0;
        virtual void _blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) =0;
        virtual CRGB _shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual CRGB _shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in = CRGB::Black) =0;
        virtual bool _paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool overlay) =0;
        virtual bool _paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool overlay) =0;
        virtual bool _paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) =0;

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
            _paintSolid(first(), last(), CRGB::Black, false);
        }

        bool rainbow(uint8_t initialHue) {
            uint8_t deltaHue = max(255 / size(), 1);
            return _paintRainbow(initialHue, deltaHue, first(), last());
        }

        bool rainbow(uint8_t initialHue, uint8_t deltaHue) {
            return _paintRainbow(initialHue, deltaHue, first(), last());
        }

        bool rainbow(uint8_t initialHue, double posFrom, double posTo) {
            uint16_t indexFrom = clamp16(posFrom);
            uint16_t indexTo = clamp16(posTo);
            uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
            return _paintRainbow(initialHue, deltaHue, indexFrom, indexTo);
        }

        bool rainbow(uint8_t initialHue, uint8_t deltaHue, double posFrom, double posTo) {
            uint16_t indexFrom = clamp16(posFrom);
            uint16_t indexTo = clamp16(posTo);
            return _paintRainbow(initialHue, deltaHue, indexFrom, indexTo);
        }

        void fade(uint8_t amount) {
            _fade(first(), last(), amount);
        }

        void fade(uint8_t amount, double posFrom, double posTo) {
            _fade(clamp16(posFrom), clamp16(posTo), amount);
        }

        void blur(uint8_t amount) {
            _blur(first(), last(), amount);
        }

        void blur(uint8_t amount, double posFrom, double posTo) {
            _blur(clamp16(posFrom), clamp16(posTo), amount);
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
        
        void paint(CRGB color, bool overlay) {
            _paintSolid(first(), last(), color, overlay);
        }

        void paint(CHSV color, bool overlay) {
            CRGB rgb;
            hsv2rgb_rainbow(color, rgb);
            _paintSolid(first(), last(), rgb, overlay);
        }

        void paint(Gradient *gradient, double gradientFrom, double gradientTo, bool overlay) {
            _paintGradient(first(), last(), gradient, gradientFrom, gradientTo, overlay);
        }

        bool paint(double pos, CRGB color, bool overlay) {
            return _paintSolid(clamp16(pos), clamp16(pos), color, overlay);
        }

        bool paint(double posFrom, double posTo, CRGB color, bool overlay) {
            return _paintSolid(clamp16(posFrom), clamp16(posTo), color, overlay);
        }

        bool paint(double posFrom, double posTo, Gradient *gradient, double gradientFrom, double gradientTo, bool overlay) {
            return _paintGradient(clamp16(posFrom), clamp16(posTo), gradient, gradientFrom, gradientTo, overlay);
        }

        bool paintNormalized(double normPos, CRGB color, bool overlay) {
            return _paintSolid(fromNormalizedPosition(normPos), fromNormalizedPosition(normPos), color, overlay);
        }

        bool paintNormalized(double normPosFrom, double norPosTo, CRGB color, bool overlay) {
            return _paintSolid(fromNormalizedPosition(normPosFrom), fromNormalizedPosition(norPosTo), color, overlay);
        }

        bool paintRandomPos(int16_t length, CRGB color, bool overlay) {
            uint16_t pos = random16(size() - length);
            return _paintSolid(pos, pos + length, color, overlay);
        }

        CRGB getPosition(double normPos) {
            return getIndex(fromNormalizedPosition(normPos));
        }

        virtual void flush() {};        
        virtual Strip *overlay(double opacity = 1) =0;
        virtual uint16_t size() =0;
        virtual bool paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool overlay) =0;
        virtual CRGB getIndex(int16_t index) =0;
};

#endif
