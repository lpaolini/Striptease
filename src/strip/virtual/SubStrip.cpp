#include "SubStrip.h"

SubStrip::SubStrip(Strip *strip, int16_t start, int16_t end) {
    this->strip = strip;
    this->start = max(0, start);
    this->end = min(strip->last(), end);
}

Strip *SubStrip::overlay(double opacity) {
    return new BufferedStrip(this, opacity);
}

uint16_t SubStrip::size() {
    return end - start + 1;
}

int16_t SubStrip::toStrip(int16_t index) {
    return start + index;
}

void SubStrip::_fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

void SubStrip::_blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

CRGB SubStrip::_shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftUp(toStrip(indexFrom), toStrip(indexTo), in);
    }
    return CRGB::Black;
}

CRGB SubStrip::_shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexFrom), toStrip(indexTo), in);
    }
    return CRGB::Black;
}

bool SubStrip::_paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexFrom), toStrip(indexTo), color, add);
    }
    return false;
}

bool SubStrip::_paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexFrom), toStrip(indexTo), gradient, gradientFrom, gradientTo, add);
    }
    return false;
}

bool SubStrip::_paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) {
    if (crop(indexFrom, indexTo)) {
        return strip->rainbow(initialHue, deltaHue, toStrip(indexFrom), toStrip(indexTo));
    }
    return false;
}

bool SubStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t indexFrom = fromNormalizedPosition(positionFrom, size);
    uint16_t indexTo = indexFrom + size - 1;
    return paint(indexFrom, indexTo, color, add);
}

CRGB SubStrip::getIndex(int16_t index) {
    if (isInRange(index)) {
        return strip->getIndex(toStrip(index));
    }
    return CRGB::Black;
}
