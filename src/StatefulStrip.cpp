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

uint16_t StatefulStrip::random() {
    return random16(size());
}

uint16_t StatefulStrip::randomExclude(uint16_t excludeIndex, uint16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t StatefulStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t StatefulStrip::fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

bool StatefulStrip::isInRange(int16_t index) {
    return index >= 0 && index < size();
}

uint16_t StatefulStrip::limitToRange(int16_t index) {
    return max(min(index, last()), 0);
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

void StatefulStrip::rainbow(uint8_t initialHue, uint16_t indexFrom, uint16_t indexTo) {
    uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
    rainbow(initialHue, deltaHue, indexFrom, indexTo);
}

void StatefulStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, uint16_t indexFrom, uint16_t indexTo) {
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).fill_rainbow(initialHue, deltaHue);
}

void StatefulStrip::fade(uint8_t amount) {
    leds->fadeToBlackBy(amount);
}

void StatefulStrip::fade(uint8_t amount, uint16_t indexFrom, uint16_t indexTo) {
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).fadeToBlackBy(amount);
}

void StatefulStrip::blur(uint8_t amount) {
    leds->blur1d(amount);
}

void StatefulStrip::blur(uint8_t amount, uint16_t indexFrom, uint16_t indexTo) {
    (*leds)(limitToRange(indexFrom), limitToRange(indexTo)).blur1d(amount);
}

CRGB StatefulStrip::shiftUp(CRGB in) {
    return shiftUp(first(), last(), in);
}

CRGB StatefulStrip::shiftUp(uint16_t indexFrom, uint16_t indexTo, CRGB in) {
    uint16_t firstIndex = limitToRange(indexFrom);
    uint16_t lastIndex = limitToRange(indexTo);
    if (lastIndex > firstIndex) {
        CRGB out = (*leds)[lastIndex];
        for (uint16_t i = lastIndex; i > firstIndex ; i--) {
            (*leds)[i] = (*leds)[i - 1];
        }
        (*leds)[firstIndex] = in;
        return out;
    } else {
        return in;
    }
}

CRGB StatefulStrip::shiftDown(CRGB in) {
    return shiftDown(first(), last(), in);
}

CRGB StatefulStrip::shiftDown(uint16_t indexFrom, uint16_t indexTo, CRGB in) {
    uint16_t firstIndex = limitToRange(indexFrom);
    uint16_t lastIndex = limitToRange(indexTo);
    if (lastIndex > firstIndex) {
        CRGB out = (*leds)[firstIndex];
        for (uint16_t i = firstIndex; i < lastIndex; i++) {
            (*leds)[i] = (*leds)[i + 1];
        }
        (*leds)[lastIndex] = in;
        return out;
    } else {
        return in;
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
    int16_t posMin = min(indexFrom, indexTo);
    int16_t posMax = max(indexFrom, indexTo);
    if (isInRange(posMin) || isInRange(posMax)) {
        if (add) {
            (*leds)(limitToRange(posMin), limitToRange(posMax)) |= color;
        } else {
            (*leds)(limitToRange(posMin), limitToRange(posMax)) = color;
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

bool StatefulStrip::paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size - 1, color, add);
}

bool StatefulStrip::paintRandomPos(uint16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
