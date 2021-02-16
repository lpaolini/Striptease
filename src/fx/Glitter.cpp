#include "Glitter.h"

Glitter::Glitter(Strip *strip, State *state) : Fx(strip, state) {}

void Glitter::reset() {
    clear();
    fadeTimer.reset();
    timer.reset();
}

void Glitter::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(max(1, 20 * state->linearFxSpeed));
    }
    if (timer.isElapsed(100 * (1 - state->linearFxSpeed))) {
        uint16_t pos = random16(strip->size() - SEGMENT_LENGTH);
        strip->paint(pos, pos + (SEGMENT_LENGTH - 1), CHSV(state->slowRotatingHue + random8(64), 255, 255));
    }
}
