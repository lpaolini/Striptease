#include "SubStrip.h"

SubStrip::SubStrip(Strip *strip, int16_t start, int16_t end) {
    this->strip = strip;
    this->start = max(0, start);
    this->end = min(strip->last(), end);
}

Strip *SubStrip::buffered(uint8_t opacity) {
    return new BufferedStrip(this, opacity);
}

uint16_t SubStrip::size() {
    return end - start + 1;
}

int16_t SubStrip::toStrip(int16_t index) {
    return start + index;
}

void SubStrip::off() {
    paint(CRGB::Black);
}

void SubStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->rainbow(initialHue, deltaHue, toStrip(indexFrom), toStrip(indexTo));
    }
}

void SubStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

void SubStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

CRGB SubStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftUp(toStrip(indexFrom), toStrip(indexTo), in);
    }
    return CRGB::Black;
}

CRGB SubStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexFrom), toStrip(indexTo), in);
    }
    return CRGB::Black;
}

void SubStrip::paint(CRGB color, bool add) {
    strip->paint(color, add);
}

bool SubStrip::paint(int16_t index, CRGB color, bool add) {
    if (isInRange(index)) {
        return strip->paint(toStrip(index), color, add);
    }
    return false;
}

bool SubStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexFrom), toStrip(indexTo), color, add);
    }
    return false;
}

bool SubStrip::paintNormalized(double positionFrom, double positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool SubStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t indexFrom = fromNormalizedPosition(positionFrom, size);
    uint16_t indexTo = indexFrom + size - 1;
    return paint(indexFrom, indexTo, color, add);
}

bool SubStrip::paintRandomPos(int16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}

CRGB SubStrip::getIndex(int16_t index) {
    if (isInRange(index)) {
        return strip->getIndex(toStrip(index));
    }
    return CRGB::Black;
}

CRGB SubStrip::getPosition(double position) {
    return getIndex(fromNormalizedPosition(position));
}
