#include "Rainbow.h"

Rainbow::Rainbow(Strip *strip, State *state, uint8_t phase) {
    this->strip = strip;
    this->state = state;
    this->phase = phase;
}

void Rainbow::reset() {
    clear(strip);
}

void Rainbow::loop() {
    strip->rainbow(state->fastRotatingHue + phase);
}
