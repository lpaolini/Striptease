#include "ReversedStrip.h"

ReversedStrip::ReversedStrip(Strip *strip) {
    this->strip = strip;
}

Strip *ReversedStrip::buffered(uint8_t opacity) {
    return new BufferedStrip(this, opacity);
}

uint16_t ReversedStrip::size() {
    return strip->size();
}

int16_t ReversedStrip::toStrip(int16_t index) {
    return strip->last() - index;
}

void ReversedStrip::off() {
    strip->off();
}

void ReversedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->rainbow(initialHue + (indexTo - indexFrom + 1) * deltaHue, -deltaHue, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

CRGB ReversedStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexTo), toStrip(indexFrom), in);
    }
    return CRGB::Black;
}

CRGB ReversedStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftUp(toStrip(indexTo), toStrip(indexFrom), in);
    }
    return CRGB::Black;
}

void ReversedStrip::paint(CRGB color, bool add) {
    strip->paint(color, add);
}

bool ReversedStrip::paint(int16_t index, CRGB color, bool add) {
    return strip->paint(toStrip(index), color, add);
}

bool ReversedStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexTo), toStrip(indexFrom), color, add);
    }
    return false;
}

bool ReversedStrip::paintNormalized(double positionFrom, double positionTo, CRGB color, bool add) {
    return strip->paintNormalized(1 - positionFrom, 1 - positionTo, color, add);
}

bool ReversedStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    return strip->paintNormalizedSize(1 - positionFrom, size, color, add);
}

bool ReversedStrip::paintRandomPos(int16_t length, CRGB color, bool add) {
    return strip->paintRandomPos(length, color, add);
}

CRGB ReversedStrip::getIndex(int16_t index) {
    if (isInRange(index)) {
        return strip->getIndex(toStrip(index));
    }
    return CRGB::Black;
}

CRGB ReversedStrip::getPosition(double position) {
    return getIndex(fromNormalizedPosition(position));
}
