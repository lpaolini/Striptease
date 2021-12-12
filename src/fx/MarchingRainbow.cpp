#include "MarchingRainbow.h"

MarchingRainbow::MarchingRainbow(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void MarchingRainbow::beforeRender() {
    t1 = int1.time(.1, state->linearFxSpeed);
    t2 = int2.time(.05, state->linearFxSpeed);
}

CRGB MarchingRainbow::render(int16_t index, double x) {
    double w1 = wave(t1 + x);
    double w2 = wave(t2 - 10 * x + .2);
    double v = w1 - w2;
    double h = wave(wave(wave(t1 + x)) - x);
    return hsv(h, 1, v);
}
