#include "JoinedStrip.h"

JoinedStrip::JoinedStrip(Strip *strip1, Strip *strip2) {
    this->strip1 = strip1;
    this->strip2 = strip2;
}

uint16_t JoinedStrip::size() {
    return strip1->size() + strip2->size();
}

uint16_t JoinedStrip::first() {
    return strip1->first();
}

uint16_t JoinedStrip::center() {
    return size() / 2;    
}

uint16_t JoinedStrip::last() {
    return size() -1;
}

uint16_t JoinedStrip::random() {
    return random16(size());
}

uint16_t JoinedStrip::randomExclude(uint16_t excludeIndex, uint16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t JoinedStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t JoinedStrip::fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

bool JoinedStrip::isInRange(int16_t index) {
    return index >= 0 && index < size();
}

uint16_t JoinedStrip::limitToRange(int16_t index) {
    return max(min(index, last()), 0);
}

void JoinedStrip::off() {
    strip1->off();
    strip2->off();
}

void JoinedStrip::rainbow(uint8_t initialHue) {
    strip1->rainbow(initialHue); // TODO: it's wrong
    strip2->rainbow(initialHue); // TODO: it's wrong
}

void JoinedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    strip1->rainbow(initialHue, deltaHue); // TODO: it's wrong
    strip2->rainbow(initialHue, deltaHue); // TODO: it's wrong
}

void JoinedStrip::fade(uint8_t amount) {
    strip1->fade(amount);
    strip2->fade(amount);
}

void JoinedStrip::blur(uint8_t amount) { // TODO: this is not correct across boundary
    strip1->blur(amount);
    strip2->blur(amount);
}

CRGB JoinedStrip::shiftUp(CRGB in) {
    return strip2->shiftUp(strip1->shiftUp(in));
}

CRGB JoinedStrip::shiftDown(CRGB in) {
    return strip1->shiftDown(strip2->shiftDown(in));
}

void JoinedStrip::paint(CRGB color, bool add) {
    strip1->paint(color, add);
    strip2->paint(color, add);
}

bool JoinedStrip::paint(int16_t index, CRGB color, bool add) {
    if (strip1->isInRange(index)) {
        return strip1->paint(index, color, add);
    } else {
        return strip2->paint(index - strip1->size(), color, add);
    }
}

bool JoinedStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            return strip1->paint(indexFrom, indexTo, color, add);
        } else {
            bool s1 = strip1->paint(indexFrom, strip1->last(), color, add);
            bool s2 = strip1->paint(strip2->first(), indexTo - strip1->size(), color, add);
            return s1 || s2;
        }
    } else {
        return strip2->paint(indexFrom - strip1->size(), indexTo - strip1->size(), color, add);
    }
}

bool JoinedStrip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool JoinedStrip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool JoinedStrip::paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size, color, add);
}

bool JoinedStrip::paintRandomPos(uint16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
