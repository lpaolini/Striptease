#include "ReversedStrip.h"

ReversedStrip::ReversedStrip(Strip *strip) {
    this->strip = strip;
}

Strip *ReversedStrip::buffered() {
    return new BufferedStrip(this);
}

uint16_t ReversedStrip::size() {
    return strip->size();
}

uint16_t ReversedStrip::first() {
    return strip->first();
}

uint16_t ReversedStrip::center() {
    return strip->center();    
}

uint16_t ReversedStrip::last() {
    return strip->last();    
}

bool ReversedStrip::isInRange(int16_t index) {
    return strip->isInRange(index);
}

uint16_t ReversedStrip::limitToRange(int16_t index) {
    return strip->limitToRange(index);
}

uint16_t ReversedStrip::random() {
    return strip->random();
}

uint16_t ReversedStrip::randomExclude(int16_t excludeIndex, int16_t excludeCount) {
    return strip->randomExclude(excludeIndex, excludeCount);
}

uint16_t ReversedStrip::randomInRange(double from, double to) {
    return strip->randomInRange(from, to);
}

uint16_t ReversedStrip::fromNormalizedPosition(double normalizedPosition, int16_t excludeCount) {
    return strip->fromNormalizedPosition(normalizedPosition, excludeCount);
}

int16_t ReversedStrip::toStrip(int16_t index) {
    return strip->last() - index;
}

void ReversedStrip::off() {
    strip->off();
}

void ReversedStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, first(), last());
}

void ReversedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    rainbow(initialHue, deltaHue, first(), last());
}

void ReversedStrip::rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
        rainbow(initialHue, deltaHue, indexFrom, indexTo);
    }
}

void ReversedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->rainbow(initialHue + (indexTo - indexFrom + 1) * deltaHue, -deltaHue, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::fade(uint8_t amount) {
    strip->fade(amount);
}

void ReversedStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->fade(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

void ReversedStrip::blur(uint8_t amount) {
    strip->blur(amount);
}

void ReversedStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        strip->blur(amount, toStrip(indexTo), toStrip(indexFrom));
    }
}

CRGB ReversedStrip::shiftUp(CRGB in) {
    return shiftUp(first(), last(), in);
}

CRGB ReversedStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        return strip->shiftDown(toStrip(indexTo), toStrip(indexFrom), in);
    }
    return CRGB::Black;
}

CRGB ReversedStrip::shiftDown(CRGB in) {
    return shiftDown(first(), last(), in);
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

bool ReversedStrip::paintNormalized(double position, CRGB color, bool add) {
    return strip->paintNormalized(1 - position, color, add);
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
