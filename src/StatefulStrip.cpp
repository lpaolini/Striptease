#include "StatefulStrip.h"

StatefulStrip::StatefulStrip(CRGBSet &leds, uint16_t density) {
    this->leds = &leds;
    this->density = density;
}

StatefulStrip::StatefulStrip(CRGBSet *leds, uint16_t density) {
    this->leds = leds;
    this->density = density;
}

StatefulStrip::StatefulStrip() {}

void StatefulStrip::setLeds(CRGBSet *leds) {
    this->leds = leds;
}

uint16_t StatefulStrip::size() {
    return leds->size();
}

uint16_t StatefulStrip::first() {
    return 0;
}

uint16_t StatefulStrip::center() {
    return size() / 2;    
}

uint16_t StatefulStrip::last() {
    return size() - 1;    
}

bool StatefulStrip::isInRange(int16_t index) {
    return index >= first() && index <= last();
}

uint16_t StatefulStrip::limitToRange(int16_t index) {
    return max(min(index, last()), first());
}

uint16_t StatefulStrip::random() {
    return random16(size());
}

uint16_t StatefulStrip::randomExclude(int16_t excludeIndex, int16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t StatefulStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t StatefulStrip::fromNormalizedPosition(float normalizedPosition, int16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

void StatefulStrip::off() {
    paint(CRGB::Black);
}

void StatefulStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, first(), last());
}

void StatefulStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    rainbow(initialHue, deltaHue, first(), last());
}

void StatefulStrip::rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
    rainbow(initialHue, deltaHue, indexFrom, indexTo);
}

void StatefulStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).fill_rainbow(initialHue, deltaHue);
}

void StatefulStrip::fade(uint8_t amount) {
    leds->fadeToBlackBy(amount);
}

void StatefulStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).fadeToBlackBy(amount);
}

void StatefulStrip::blur(uint8_t amount) {
    leds->blur1d(amount);
}

void StatefulStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).blur1d(amount);
}

CRGB StatefulStrip::shiftUp(CRGB in) {
    return shiftUp(first(), last(), in);
}

CRGB StatefulStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    sanitize(indexFrom, indexTo);
    if (indexFrom == indexTo) {
        return in;
    } else {
        CRGB out = (*leds)[indexTo];
        for (uint16_t i = indexTo; i > indexFrom ; i--) {
            (*leds)[i] = (*leds)[i - 1];
        }
        (*leds)[indexFrom] = in;
        return out;
    }
}

CRGB StatefulStrip::shiftDown(CRGB in) {
    return shiftDown(first(), last(), in);
}

CRGB StatefulStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    sanitize(indexFrom, indexTo);
    if (indexFrom == indexTo) {
        return in;
    } else {
        CRGB out = (*leds)[indexFrom];
        for (uint16_t i = indexFrom; i < indexTo; i++) {
            (*leds)[i] = (*leds)[i + 1];
        }
        (*leds)[indexTo] = in;
        return out;
    }
}

void StatefulStrip::paint(CRGB color, bool add) {
    if (add) {
        *leds |= color;
    } else {
        *leds = color;
    }
}

bool StatefulStrip::paint(int16_t index, CRGB color, bool add) {
    if (isInRange(index)) {
        if (add) {
            (*leds)[index] |= color;
        } else {
            (*leds)[index] = color;
        }
        return true;
    }
    return false;
}

bool StatefulStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (isInRange(indexFrom) || isInRange(indexTo)) {
        sanitize(indexFrom, indexTo);
    // if (posMin <= last() && posMax >= first()) {
        if (add) {
            (*leds)(indexFrom, indexTo) |= color;
        } else {
            (*leds)(indexFrom, indexTo) = color;
        }
        return true;
    }
    return false;
}

bool StatefulStrip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool StatefulStrip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool StatefulStrip::paintNormalizedSize(float positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size - 1, color, add);
}

bool StatefulStrip::paintRandomPos(int16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
