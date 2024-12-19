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

void StatefulStrip::off() {
    paint(CRGB::Black);
}

void StatefulStrip::rainbow(uint8_t initialHue, uint8_t deltaHue, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).fill_rainbow(initialHue, deltaHue);
    }
}

void StatefulStrip::fade(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).fadeToBlackBy(amount);
    }
}

void StatefulStrip::blur(uint8_t amount, int16_t indexFrom, int16_t indexTo) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).blur1d(amount);
    }
}

CRGB StatefulStrip::shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
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
    return CRGB::Black;
}

CRGB StatefulStrip::shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
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
    return CRGB::Black;
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
    if (crop(indexFrom, indexTo)) {
        if (add) {
            (*leds)(indexFrom, indexTo) |= color;
        } else {
            (*leds)(indexFrom, indexTo) = color;
        }
        return true;
    }
    return false;
}

bool StatefulStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t indexFrom = fromNormalizedPosition(positionFrom, size);
    uint16_t indexTo = indexFrom + size - 1;
    return paint(indexFrom, indexTo, color, add);
}

CRGB StatefulStrip::getIndex(int16_t index) {
    return (*leds)[index];
}
