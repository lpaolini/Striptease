#include "JoinedStrip.h"
#include "PhysicalStrip.h"

JoinedStrip::JoinedStrip(Strip *strip1, Strip *strip2, uint16_t gap) {
    this->strip1 = strip1;
    this->strip2 = strip2;
    this->gap = gap;
    buffer = new CRGB[gap];
    bufferSet = new CRGBSet(buffer, gap);
    gapStrip = new PhysicalStrip(bufferSet);
}

Strip *JoinedStrip::buffered() {
    return new BufferedStrip(this);
}

uint16_t JoinedStrip::size() {
    return strip1->size() + gap + strip2->size();
}

uint16_t JoinedStrip::first() {
    return strip1->first();
}

uint16_t JoinedStrip::center() {
    return size() / 2;    
}

uint16_t JoinedStrip::last() {
    return size() - 1;
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
    gapStrip->off();
}

void JoinedStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, first(), last());
}

void JoinedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    rainbow(initialHue, deltaHue, first(), last());
}

void JoinedStrip::rainbow(uint8_t initialHue, uint16_t indexFrom, uint16_t indexTo) {
    uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
    rainbow(initialHue, deltaHue, indexFrom, indexTo);
}

void JoinedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, uint16_t indexFrom, uint16_t indexTo) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            strip1->rainbow(initialHue, deltaHue, indexFrom, indexTo);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            strip1->rainbow(initialHue, deltaHue, indexFrom, strip1->last());
            gapStrip->rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue);
            strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, strip2->first(), indexTo - strip1->size());
        } else {
            // starts in strip 1 and ends in gap
            strip1->rainbow(initialHue, deltaHue, indexFrom, strip1->last());
            gapStrip->rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue);
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        strip2->rainbow(initialHue, deltaHue, indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap);
    } else {
        // starts in gap and ends in strip 2
        gapStrip->rainbow(initialHue, deltaHue, indexFrom - strip1->size(), gap - 1);
        strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, 0, indexTo - strip1->size() - gap);
    }
}

void JoinedStrip::fade(uint8_t amount) {
    strip1->fade(amount);
    gapStrip->fade(amount);
    strip2->fade(amount);
}

void JoinedStrip::fade(uint8_t amount, uint16_t indexFrom, uint16_t indexTo) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            strip1->fade(amount, indexFrom, indexTo);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            strip1->fade(amount, indexFrom, strip1->last());
            gapStrip->fade(amount);
            strip2->fade(amount, strip2->first(), indexTo - strip1->size());
        } else {
            // starts in strip 1 and ends in gap
            strip1->fade(amount, indexFrom, strip1->last());
            gapStrip->fade(amount, 0, indexTo - strip1->size());
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        strip2->fade(amount, indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap);
    } else {
        // starts in gap and ends in strip 2
        gapStrip->fade(amount, indexFrom - strip1->size(), gap - 1);
        strip2->fade(amount, 0, indexTo - strip1->size() - gap);
    }
}

void JoinedStrip::blur(uint8_t amount) {
    strip1->blur(amount);
    gapStrip->blur(amount);
    strip2->blur(amount);
}

void JoinedStrip::blur(uint8_t amount, uint16_t indexFrom, uint16_t indexTo) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            strip1->blur(amount, indexFrom, indexTo);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            strip1->blur(amount, indexFrom, strip1->last());
            // bufferSet->blur1d(amount);
            gapStrip->blur(amount);
            strip2->blur(amount, strip2->first(), indexTo - strip1->size());
        } else {
            // starts in strip 1 and ends in gap
            strip1->blur(amount, indexFrom, strip1->last());
            gapStrip->blur(amount, 0, indexTo - strip1->size());
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        strip2->blur(amount, indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap);
    } else {
        // starts in gap and ends in strip 2
        gapStrip->blur(amount, indexFrom - strip1->size(), gap - 1);
        strip2->blur(amount, 0, indexTo - strip1->size() - gap);
    }
}

CRGB JoinedStrip::shiftUp(CRGB in) {
    return strip2->shiftUp(gapStrip->shiftUp(strip1->shiftUp(in)));
}

CRGB JoinedStrip::shiftUp(uint16_t indexFrom, uint16_t indexTo, CRGB in) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            return strip1->shiftUp(indexFrom, indexTo, in);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            return strip2->shiftUp(strip2->first(), indexTo - strip1->size(), gapStrip->shiftUp(strip1->shiftUp(indexFrom, strip1->last(), in)));
        } else {
            // starts in strip 1 and ends in gap
            return gapStrip->shiftUp(0, indexTo - strip1->size(), strip1->shiftUp(indexFrom, strip1->last(), in));
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        return strip2->shiftUp(indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap, in);
    } else {
        // starts in gap and ends in strip 2
        return strip2->shiftUp(0, indexTo - strip1->size() - gap, gapStrip->shiftUp(indexFrom - strip1->size(), gap - 1, in));
    }
}

CRGB JoinedStrip::shiftDown(CRGB in) {
    return strip1->shiftDown(gapStrip->shiftDown(strip2->shiftDown(in)));
}

CRGB JoinedStrip::shiftDown(uint16_t indexFrom, uint16_t indexTo, CRGB in) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            return strip1->shiftDown(indexFrom, indexTo, in);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            return strip1->shiftDown(indexFrom, strip1->last(), gapStrip->shiftDown(strip2->shiftDown(strip2->first(), indexTo - strip1->size(), in)));
        } else {
            // starts in strip 1 and ends in gap
            return strip1->shiftDown(indexFrom, strip1->last(), gapStrip->shiftDown(0, indexTo - strip1->size(), in));
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        return strip2->shiftDown(indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap, in);
    } else {
        // starts in gap and ends in strip 2
        return gapStrip->shiftDown(indexFrom - strip1->size(), gap - 1, strip2->shiftDown(0, indexTo - strip1->size() - gap, in));
    }
}

void JoinedStrip::paint(CRGB color, bool add) {
    strip1->paint(color, add);
    gapStrip->paint(color, add);
    strip2->paint(color, add);
}

bool JoinedStrip::paint(int16_t index, CRGB color, bool add) {
    if (strip1->isInRange(index)) {
        return strip1->paint(index, color, add);
    } else if (strip2->isInRange(index - strip1->size() - gap)) {
        return strip2->paint(index - strip1->size() - gap, color, add);
    } else {
        return gapStrip->paint(index - strip1->size(), color, add);
        // return false;
    }
}

bool JoinedStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (strip1->isInRange(indexFrom)) {
        if (strip1->isInRange(indexTo)) {
            // starts and ends in strip 1
            return strip1->paint(indexFrom, indexTo, color, add);
        } else if (strip2->isInRange(indexTo - strip1->size() - gap)) {
            // starts in strip 1 and ends in strip 2
            bool s1 = strip1->paint(indexFrom, strip1->last(), color, add);
            gapStrip->paint(color, add);
            bool s2 = strip2->paint(strip2->first(), indexTo - strip1->size(), color, add);
            return s1 || s2;
        } else {
            // starts in strip 1 and ends in gap
            gapStrip->paint(0, indexTo - strip1->size(), color, add);
            return strip1->paint(indexFrom, strip1->last(), color, add);
        }
    } else if (strip2->isInRange(indexFrom - strip1->size() - gap)) {
        // starts and ends in strip 2
        return strip2->paint(indexFrom - strip1->size() - gap, indexTo - strip1->size() - gap, color, add);
    } else {
        // starts in gap and ends in strip 2
        gapStrip->paint(indexFrom - strip1->size(), gap - 1, color, add);
        return strip2->paint(0, indexTo - strip1->size() - gap, color, add);
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
    return paint(start, start + size - 1, color, add);
}

bool JoinedStrip::paintRandomPos(uint16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
