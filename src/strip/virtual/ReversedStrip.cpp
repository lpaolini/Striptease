#include "ReversedStrip.h"

ReversedStrip::ReversedStrip(Strip *strip) {
    this->strip = strip;
}

Strip *ReversedStrip::overlay(double opacity) {
    return new BufferedStrip(this, opacity);
}

uint16_t ReversedStrip::size() {
    return strip->size();
}

int16_t ReversedStrip::toStrip(int16_t index) {
    return strip->last() - index;
}

void ReversedStrip::_rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->rainbow(initialHue + (indexTo - indexFrom + 1) * deltaHue, -deltaHue, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::_fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::_blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

CRGB ReversedStrip::_shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexTo), toStrip(indexFrom), in);
    }
    return CRGB::Black;
}

CRGB ReversedStrip::_shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftUp(toStrip(indexTo), toStrip(indexFrom), in);
    }
    return CRGB::Black;
}

bool ReversedStrip::_paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexTo), toStrip(indexFrom), color, add);
    }
    return false;
}

bool ReversedStrip::_paint(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexTo), toStrip(indexFrom), gradient, gradientTo, gradientFrom, add);
    }
    return false;
}

bool ReversedStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    return strip->paintNormalizedSize(1 - positionFrom, size, color, add);
}

CRGB ReversedStrip::getIndex(int16_t index) {
    if (isInRange(index)) {
        return strip->getIndex(toStrip(index));
    }
    return CRGB::Black;
}
