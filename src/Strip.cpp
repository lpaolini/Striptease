#include "Strip.h"

Strip::Strip(CRGBSet &leds, uint16_t density) {
    this->leds = &leds;
    this->count = this->leds->size();
    this->length = float(this->count) / density;
}

void Strip::off() {
    *leds = CRGB::Black;
}

void Strip::fill(CRGB color) {
    *leds = color;
}

void Strip::fullRainbow(uint8_t initialHue) {
    leds->fill_rainbow(initialHue, max(256 / count, 1));
}

void Strip::fade(uint8_t amount) {
    leds->fadeToBlackBy(amount);
}

uint16_t Strip::toPosition(float x) {
    return int(x * (count - 1) / length);
}

uint16_t Strip::toNormalizedPosition(float x, uint16_t excludeCount) {
    return int(x * (count - 1 - excludeCount));
}

bool Strip::isInRange(int16_t position) {
    return position >= 0 && position < count;
}

uint16_t Strip::limitToRange(int16_t position) {
    return max(min(position, count - 1), 0);
}

void Strip::shiftUp() {
    // (*leds)(1, count - 1) = (*leds)(0, count - 2);
    for (int i = count - 1; i > 0 ; i--) {
        (*leds)[i] = (*leds)[i - 1];
    }
}

void Strip::shiftDown() {
    // (*leds)(0, count - 2) = (*leds)(1, count - 1);
    for (int i = 0; i < count - 1; i++) {
        (*leds)[i] = (*leds)[i + 1];
    }
}

uint16_t Strip::randomPos(uint16_t excludeCount) {
    return random16(count - excludeCount);
}

uint16_t Strip::randomPosRange(float from, float to) {
    return random16(from * count, to * count);
}

uint16_t Strip::randomPosExclude(uint16_t excludePosition, uint16_t excludeCount) {
    return (excludePosition + excludeCount + random16(count - 2 * excludeCount)) % count;
}

uint16_t Strip::centerPos() {
    return count / 2;    
}

uint16_t Strip::lastPos() {
    return count - 1;    
}

bool Strip::paint(int16_t from, int16_t to, CRGB color, bool add) {
    int16_t posMin = min(from, to);
    int16_t posMax = max(from, to);
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

bool Strip::paintNormalized(float from, float to, CRGB color, bool add) {
    return paint(toNormalizedPosition(from), toNormalizedPosition(to), color, add);
}

bool Strip::paintNormalizedSize(float from, uint16_t size, CRGB color, bool add) {
    uint16_t start = toNormalizedPosition(from, size);
    return paint(start, start + size, color, add);
}

bool Strip::paintRandomPos(uint16_t size, CRGB color, bool add) {
    uint16_t pos = randomPos(size);
    return paint(pos, pos + size, color, add);
}
