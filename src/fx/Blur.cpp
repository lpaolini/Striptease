#include "Blur.h"

Blur::Blur(Strip *strip) {
    this->strip = strip;
}

void Blur::reset() {
    clear(strip);
}

void Blur::loop() {
    uint8_t blurAmount = dim8_raw(beatsin8(3, 64, 192));       // A sinewave at 3 Hz with values ranging from 64 to 192.
    strip->leds->blur1d(blurAmount);                        // Apply some blurring to whatever's already on the strip, which will eventually go black.

    uint16_t i = beatsin16(9, 0, strip->count - 1);
    uint16_t j = beatsin16(7, 0, strip->count - 1);
    uint16_t k = beatsin16(5, 0, strip->count - 1);

    // The color of each point shifts over time, each at a different speed.
    unsigned long ms = millis();
    (*(strip->leds))[(i + j) / 2] = CHSV(ms / 29, 200, 255);
    (*(strip->leds))[(j + k) / 2] = CHSV(ms / 41, 200, 255);
    (*(strip->leds))[(k + i) / 2] = CHSV(ms / 73, 200, 255);
    (*(strip->leds))[(k + i + j) / 3] = CHSV(ms / 53, 200, 255);
}
