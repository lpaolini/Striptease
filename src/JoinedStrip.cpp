#include "JoinedStrip.h"
#include "PhysicalStrip.h"

JoinedStrip::JoinedStrip(Strip *strip1, Strip *strip2, int16_t gap) {
    this->strip1 = strip1;
    this->strip2 = strip2;
    this->gap = max(0, gap);
    buffer = new CRGB[this->gap];
    bufferSet = new CRGBSet(buffer, this->gap);
    gapStrip = new StatefulStrip(bufferSet);
}

Strip *JoinedStrip::buffered() {
    return new BufferedStrip(this);
}

uint16_t JoinedStrip::size() {
    return strip1->size() + gapStrip->size() + strip2->size();
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

bool JoinedStrip::isInRange(int16_t index) {
    return index >= first() && index <= last();
}

uint16_t JoinedStrip::limitToRange(int16_t index) {
    return max(min(index, last()), first());
}

uint16_t JoinedStrip::random() {
    return random16(size());
}

uint16_t JoinedStrip::randomExclude(int16_t excludeIndex, int16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(size() - 2 * excludeCount)) % size();
}

uint16_t JoinedStrip::randomInRange(float from, float to) {
    return random16(from * size(), to * size());
}

uint16_t JoinedStrip::fromNormalizedPosition(float normalizedPosition, int16_t excludeCount) {
    return int(normalizedPosition * (last() - excludeCount));
}

bool JoinedStrip::isInStrip1(int16_t index) {
    return strip1->isInRange(toStrip1(index));
}

bool JoinedStrip::isInGap(int16_t index) {
    return gapStrip->isInRange(toGap(index));
}

bool JoinedStrip::isInStrip2(int16_t index) {
    return strip2->isInRange(toStrip2(index));
}

int16_t JoinedStrip::toStrip1(int16_t index) {
    return index;
}

int16_t JoinedStrip::toGap(int16_t index) {
    return index - strip1->size();
}

int16_t JoinedStrip::toStrip2(int16_t index) {
    return index - strip1->size() - gapStrip->size();
}

void JoinedStrip::off() {
    strip1->off();
    gapStrip->off();
    strip2->off();
}

void JoinedStrip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, first(), last());
}

void JoinedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    rainbow(initialHue, deltaHue, first(), last());
}

void JoinedStrip::rainbow(uint8_t initialHue, int16_t indexFrom, int16_t indexTo) {
    uint8_t deltaHue = max(255 / (indexTo - indexFrom + 1), 1);
    rainbow(initialHue, deltaHue, indexFrom, indexTo);
}

void JoinedStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), toStrip1(indexTo));
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), strip1->last());
            gapStrip->rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue, gapStrip->first(), toGap(indexTo));
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), strip1->last());
            gapStrip->rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue);
            strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, strip2->first(), toStrip2(indexTo));
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        gapStrip->rainbow(initialHue, deltaHue, toGap(indexFrom), gapStrip->last());
        strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, strip2->first(), toStrip2(indexTo));
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        strip2->rainbow(initialHue, deltaHue, toStrip2(indexFrom), toStrip2(indexTo));
    }
}

void JoinedStrip::fade(uint8_t amount) {
    strip1->fade(amount);
    gapStrip->fade(amount);
    strip2->fade(amount);
}

void JoinedStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            strip1->fade(amount, toStrip1(indexFrom), toStrip1(indexTo));
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            strip1->fade(amount, toStrip1(indexFrom), strip1->last());
            gapStrip->fade(amount, gapStrip->first(), toGap(indexTo));
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            strip1->fade(amount, toStrip1(indexFrom), strip1->last());
            gapStrip->fade(amount);
            strip2->fade(amount, strip2->first(), toStrip2(indexTo));
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        gapStrip->fade(amount, toGap(indexFrom), gapStrip->last());
        strip2->fade(amount, strip2->first(), toStrip2(indexTo));
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        strip2->fade(amount, toStrip2(indexFrom), toStrip2(indexTo));
    }
}

void JoinedStrip::blur(uint8_t amount) {
    strip1->blur(amount);
    gapStrip->blur(amount);
    strip2->blur(amount);
}

void JoinedStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            strip1->blur(amount, toStrip1(indexFrom), toStrip1(indexTo));
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            strip1->blur(amount, toStrip1(indexFrom), strip1->last());
            gapStrip->blur(amount, gapStrip->first(), toGap(indexTo));
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            strip1->blur(amount, toStrip1(indexFrom), strip1->last());
            gapStrip->blur(amount);
            strip2->blur(amount, strip2->first(), toStrip2(indexTo));
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        gapStrip->blur(amount, toGap(indexFrom), gapStrip->last());
        strip2->blur(amount, strip2->first(), toStrip2(indexTo));
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        strip2->blur(amount, toStrip2(indexFrom), toStrip2(indexTo));
    }
}

CRGB JoinedStrip::shiftUp(CRGB in) {
    return strip2->shiftUp(gapStrip->shiftUp(strip1->shiftUp(in)));
}

CRGB JoinedStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            return strip1->shiftUp(toStrip1(indexFrom), toStrip1(indexTo), in);
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            CRGB fromStrip1 = strip1->shiftUp(toStrip1(indexFrom), strip1->last(), in);
            return gapStrip->shiftUp(gapStrip->first(), toGap(indexTo), fromStrip1);
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            CRGB fromStrip1 = strip1->shiftUp(toStrip1(indexFrom), strip1->last(), in);
            CRGB fromGap = gapStrip->shiftUp(fromStrip1);
            return strip2->shiftUp(strip2->first(), toStrip2(indexTo), fromGap);
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        CRGB fromGap = gapStrip->shiftUp(toGap(indexFrom), gapStrip->last(), in);
        return strip2->shiftUp(strip2->first(), toStrip2(indexTo), fromGap);
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        return strip2->shiftUp(toStrip2(indexFrom), toStrip2(indexTo), in);
    }
    return CRGB::Black;
}

CRGB JoinedStrip::shiftDown(CRGB in) {
    return strip1->shiftDown(gapStrip->shiftDown(strip2->shiftDown(in)));
}

CRGB JoinedStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            return strip1->shiftDown(toStrip1(indexFrom), toStrip1(indexTo), in);
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            CRGB fromGap = gapStrip->shiftDown(gapStrip->first(), toGap(indexTo), in);
            return strip1->shiftDown(toStrip1(indexFrom), strip1->last(), fromGap);
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            CRGB fromStrip2 = strip2->shiftDown(strip2->first(), toStrip2(indexTo), in);
            CRGB fromGap = gapStrip->shiftDown(fromStrip2);
            return strip1->shiftDown(toStrip1(indexFrom), strip1->last(), fromGap);
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        CRGB fromStrip2 = strip2->shiftDown(strip2->first(), toStrip2(indexTo), in);
        return gapStrip->shiftDown(toGap(indexFrom), gapStrip->last(), fromStrip2);
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        return strip2->shiftDown(toStrip2(indexFrom), toStrip2(indexTo), in);
    }
    return CRGB::Black;
}

void JoinedStrip::paint(CRGB color, bool add) {
    strip1->paint(color, add);
    gapStrip->paint(color, add);
    strip2->paint(color, add);
}

bool JoinedStrip::paint(int16_t index, CRGB color, bool add) {
    if (isInStrip1(index)) {
        return strip1->paint(toStrip1(index), color, add);
    } else if (isInGap(index)) {
        return gapStrip->paint(toGap(index), color, add);
    } else if (isInStrip2(index)) {
        return strip2->paint(toStrip2(index), color, add);
    }
    return false;
}

bool JoinedStrip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    sanitize(indexFrom, indexTo);
    if (isInStrip1(indexFrom)) {
        if (isInStrip1(indexTo)) {
            // starts and ends in strip 1
            return strip1->paint(toStrip1(indexFrom), toStrip1(indexTo), color, add);
        } else if (isInGap(indexTo)) {
            // starts in strip 1 and ends in gap
            bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), color, add);
            bool sg = gapStrip->paint(color, add, gapStrip->first(), toGap(indexTo));
            return s1 || sg;
            
        } else if (isInStrip2(indexTo)) {
            // starts in strip 1 and ends in strip 2
            bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), color, add);
            gapStrip->paint(color, add);
            bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), color, add);
            return s1 || s2;
        }
    } else if (isInGap(indexFrom)) {
        // starts in gap and ends in strip 2
        bool sg = gapStrip->paint(toGap(indexFrom), gapStrip->last(), color, add);
        bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), color, add);
        return sg || s2;
    } else if (isInStrip2(indexFrom)) {
        // starts and ends in strip 2
        return strip2->paint(toStrip2(indexFrom), toStrip2(indexTo), color, add);
    }
    return false;
}

bool JoinedStrip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool JoinedStrip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool JoinedStrip::paintNormalizedSize(float positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size - 1, color, add);
}

bool JoinedStrip::paintRandomPos(int16_t length, CRGB color, bool add) {
    uint16_t pos = random16(size() - length);
    return paint(pos, pos + length, color, add);
}
