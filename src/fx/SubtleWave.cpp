#include "SubtleWave.h"

SubtleWave::SubtleWave(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void SubtleWave::beforeRender() {
    t1 = int1.time(.03, state->linearFxSpeed);
    t2 = int2.time(.04, state->linearFxSpeed);
}

CRGB SubtleWave::render(int16_t index, double x) {
    double v = pow((sin(TWO_PI * (t1 - 7 * x)) + sin(TWO_PI * (t1 - 10 * x)) + 4) / 6, 2);
    return hsv(.9, 1, v);
}
