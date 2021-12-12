#include "FastPulse.h"

FastPulse::FastPulse(Strip *strip, AudioChannel *audioChannel, State *state, CRGB pulseColor) : Fx(strip, audioChannel, state) {
    this->pulseColor = pulseColor;
    reset();
}

void FastPulse::beforeRender() {
    t1 = int1.time(.1, state->linearFxSpeed);
}

CRGB FastPulse::render(int16_t index, double x) {
    double v = pow(triangle(frac(2 * wave(t1) + x)), 5);
    return v < .9 ? hsv(t1, 1, v) : pulseColor;
}
