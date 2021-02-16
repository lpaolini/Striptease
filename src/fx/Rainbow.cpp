#include "Rainbow.h"

Rainbow::Rainbow(Strip *strip, State *state, uint8_t phase) : Fx(strip, state) {
    this->phase = phase;
}

void Rainbow::reset() {
    clear();
}

void Rainbow::loop() {
    strip->rainbow(state->fastRotatingHue + phase);
}
