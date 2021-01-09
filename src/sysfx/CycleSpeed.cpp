#include "CycleSpeed.h"

CycleSpeed::CycleSpeed(Strip *strip, State *state) {
    this->strip = strip;
    this->state = state;
}

void CycleSpeed::reset() {
    clear(strip);
}

void CycleSpeed::loop() {
    strip->off();
    strip->paintNormalized(0, 1, CHSV(0, 255, 75), false);
    strip->paintNormalizedSize(state->linearCycleSpeed, 5, CHSV(0, 0, 255), false);
}
