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
        strip->paintRandomPos(SEGMENT_LENGTH, CHSV(state->rotatingHue + random8(64), 255, 255), true);
    }
}
