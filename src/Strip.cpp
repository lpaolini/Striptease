#include "Strip.h"

Strip::Strip(CRGBSet &leds, uint16_t density) {
    this->leds = &leds;
    this->density = density;
    this->count = this->leds->size();
}

uint16_t Strip::size() {
    return count;
}

uint16_t Strip::first() {
    return 0;
}

uint16_t Strip::center() {
    return count / 2;    
}

uint16_t Strip::last() {
    return count - 1;    
}

uint16_t Strip::random() {
    return random16(count);
}

uint16_t Strip::randomExclude(uint16_t excludeIndex, uint16_t excludeCount) {
    return (excludeIndex + excludeCount + random16(count - 2 * excludeCount)) % count;
}

uint16_t Strip::randomInRange(float from, float to) {
    return random16(from * count, to * count);
}

uint16_t Strip::fromNormalizedPosition(float normalizedPosition, uint16_t excludeCount) {
    return int(normalizedPosition * (count - 1 - excludeCount));
}

bool Strip::isInRange(int16_t index) {
    return index >= 0 && index < count;
}

uint16_t Strip::limitToRange(int16_t index) {
    return max(min(index, count - 1), 0);
}

void Strip::off() {
    *leds = CRGB::Black;
}

void Strip::rainbow(uint8_t initialHue) {
    rainbow(initialHue, max(255 / count, 1));
}

void Strip::rainbow(uint8_t initialHue, uint8_t deltaHue) {
    leds->fill_rainbow(initialHue, deltaHue);
}

void Strip::fade(uint8_t amount) {
    leds->fadeToBlackBy(amount);
}

void Strip::blur(uint8_t amount) {
    leds->blur1d(amount);
}

CRGB Strip::shiftUp(CRGB in) {
    CRGB out = (*leds)[count - 1];
    for (int i = count - 1; i > 0 ; i--) {
        (*leds)[i] = (*leds)[i - 1];
    }
    (*leds)[0] = in;
    return out;
}

CRGB Strip::shiftDown(CRGB in) {
    CRGB out = (*leds)[0];
    for (int i = 0; i < count - 1; i++) {
        (*leds)[i] = (*leds)[i + 1];
    }
    (*leds)[count - 1] = in;
    return out;
}

void Strip::paint(CRGB color, bool add) {
    if (add) {
        *leds |= color;
    } else {
        *leds = color;
    }
}

bool Strip::paint(int16_t index, CRGB color, bool add) {
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

bool Strip::paint(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
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

bool Strip::paintNormalized(float position, CRGB color, bool add) {
    return paint(fromNormalizedPosition(position), color, add);
}

bool Strip::paintNormalized(float positionFrom, float positionTo, CRGB color, bool add) {
    return paint(fromNormalizedPosition(positionFrom), fromNormalizedPosition(positionTo), color, add);
}

bool Strip::paintNormalizedSize(float positionFrom, uint16_t size, CRGB color, bool add) {
    uint16_t start = fromNormalizedPosition(positionFrom, size);
    return paint(start, start + size, color, add);
}

bool Strip::paintRandomPos(uint16_t size, CRGB color, bool add) {
    uint16_t pos = random16(count - size);
    return paint(pos, pos + size, color, add);
}
