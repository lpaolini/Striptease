#include "Orbit.h"

Orbit::Orbit(Strip *strip, State *state, float phase) : Fx(strip, state) {
    this->phase = phase;
    for (uint8_t i = 0; i < ITEMS; i++) {
        item[i].setup(strip, state, HUE_STEP * i, phase + ANGLE_STEP * i, SPEED_STEP * i, ECCENTRICITY, ECCENTRICITY_ANGLE);
    }
    reset();
}

void Orbit::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        item[i].reset();
    }
    timer.reset();
}

void Orbit::loop() {
    if (timer.isElapsed()) {
        strip->fade(150);
        for (uint8_t i = 0; i < ITEMS; i++) {
            item[i].loop();
        }
    }
}
