#include "Blur.h"

Blur::Blur(Strip *strip) : Fx(strip) {}

void Blur::reset() {
    clear();
}

void Blur::loop() {
    strip->blur(dim8_raw(beatsin8(3, 64, 192)));

    uint16_t i = beatsin16(9, 0, strip->last());
    uint16_t j = beatsin16(7, 0, strip->last());
    uint16_t k = beatsin16(5, 0, strip->last());

    unsigned long ms = millis();
    strip->paint((i + j) / 2, CHSV(ms / 29, 200, 255));
    strip->paint((j + k) / 2, CHSV(ms / 41, 200, 255));
    strip->paint((k + i) / 2, CHSV(ms / 73, 200, 255));
    strip->paint((k + i + j) / 3, CHSV(ms / 53, 200, 255));
}
