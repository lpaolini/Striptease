#include "Pixel.h"

Pixel::Pixel() {};

void Pixel::setup(Strip *strip) {
    this->strip = strip;
    reset();
}

void Pixel::reset() {
    first = true;
}

void Pixel::set(int pos, CRGB color, bool add) {
    if (first) {
        pos0 = pos;
        first = false;
    }

    int posMin;
    int posMax;

    if (pos == pos0) {
        posMin = pos;
        posMax = pos;
    } else {
        if (pos < pos0) {
            posMin = pos;
            posMax = pos0 - 1;        
        } else {
            posMin = pos0 + 1;
            posMax = pos;        
        }
    }

    pos0 = pos;

    strip->paint(posMin, posMax, color, add);
}

void Pixel::setNormalized(float pos, CRGB color) {
    set(pos * (strip->count - 1), color);
}
