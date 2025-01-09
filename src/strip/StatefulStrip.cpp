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

Strip *StatefulStrip::overlay(double opacity) {
    return this;
}

uint16_t StatefulStrip::size() {
    return leds->size();
}

void StatefulStrip::_fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).fadeToBlackBy(amount);
    }
}

void StatefulStrip::_blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).blur1d(amount);
    }
}

CRGB StatefulStrip::_shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
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

CRGB StatefulStrip::_shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
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

bool StatefulStrip::_paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
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

bool StatefulStrip::_paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool add) {
    if (crop(indexFrom, indexTo)) {
        for (uint16_t i = indexFrom; i < indexTo; i++) {
            CRGB color = gradient->getColor(gradientFrom + (gradientTo - gradientFrom) * (i - indexFrom) / (indexTo - indexFrom));
            if (add) {
                (*leds)[i] |= color;
            } else {
                (*leds)[i] = color;
            }
        }
        return true;
    }
    return false;
}

bool StatefulStrip::_paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) {
    if (crop(indexFrom, indexTo)) {
        (*leds)(indexFrom, indexTo).fill_rainbow(initialHue, deltaHue);
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
