#include "SubStrip.h"

SubStrip::SubStrip(Strip *strip, int16_t start, int16_t end) {
    this->strip = strip;
    this->start = max(0, start);
    this->end = min(strip->last(), end);
}

Strip *SubStrip::buffered() {
    return new BufferedStrip(this);
}

uint16_t SubStrip::size() {
    return end - start + 1;
}

uint16_t SubStrip::first() {
    return 0;
}

uint16_t SubStrip::center() {
    return size() / 2;
}

uint16_t SubStrip::last() {
    return size() - 1;
}

bool SubStrip::isInRange(int16_t index) {
    return index >= first() && index <= last();
}

uint16_t SubStrip::limitToRange(int16_t index) {
    return max(min(index, last()), first());
}

uint16_t SubStrip::random() {
    return random16(size());
}

uint16_t SubStrip::randomExclude(int16_t excludeIndex, int16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t SubStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t SubStrip::fromNormalizedPosition(float normalizedPosition, int16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

int16_t SubStrip::toStrip(int16_t index) {
    return start + index;
}

void SubStrip::off() {
    paint(CRGB::Black);
}

void SubStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, first(), last());
}

void SubStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    rainbow(initialHue, deltaHue, first(), last());
}

void SubStrip::rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
        rainbow(initialHue, deltaHue, indexFrom, indexTo);
    }
}

void SubStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->rainbow(initialHue, deltaHue, toStrip(indexFrom), toStrip(indexTo));
    }
}

void SubStrip::fade(uint8_t amount) {
    fade(amount, first(), last());
}

void SubStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

void SubStrip::blur(uint8_t amount) {
    blur(amount, first(), last());
}

void SubStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexFrom), toStrip(indexTo));
    }
}

CRGB SubStrip::shiftUp(CRGB in) {
    return shiftUp(first(), last(), in);
}

CRGB SubStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftUp(toStrip(indexFrom), toStrip(indexTo), in);
    }
}

CRGB SubStrip::shiftDown(CRGB in) {
    return shiftDown(first(), last(), in);
}

CRGB SubStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexFrom), toStrip(indexTo), in);
    }
}

void SubStrip::paint(CRGB color, bool add) {
    strip->paint(start, end, color, add);
}

bool SubStrip::paint(int16_t index, CRGB color, bool add) {
    if (isInRange(index)) {
        return strip->paint(toStrip(index), color, add);
    }
}

bool SubStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        return strip->paint(toStrip(indexFrom), toStrip(indexTo), color, add);
    }
}

bool SubStrip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool SubStrip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool SubStrip::paintNormalizedSize(float positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t indexFrom = fromNormalizedPosition(positionFrom, size);
    uint16_t indexTo = indexFrom + size - 1;
    return paint(indexFrom, indexTo, color, add);
}

bool SubStrip::paintRandomPos(int16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
