#include "SpeedMeter.h"

SpeedMeter::SpeedMeter(Strip *strip, State *state) {
    this->strip = strip;
    this->state = state;
}

void SpeedMeter::reset() {
    clear(strip);
}

void SpeedMeter::loop() {
    strip->off();
    strip->paintNormalized(0, 1, CHSV(180, 255, 75), false);
    strip->paintNormalizedSize(state->linearFxSpeed, 5, CHSV(0, 0, 255), false);
}
