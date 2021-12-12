#include "RippleReflections.h"

RippleReflections::RippleReflections(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void RippleReflections::beforeRender() {
    t1 = TWO_PI * int1.time(.03, state->linearFxSpeed);
    t2 = TWO_PI * int2.time(.05, state->linearFxSpeed);
    t3 = TWO_PI * int3.time(.04, state->linearFxSpeed);
}

CRGB RippleReflections::render(int16_t index, double x) {
    double a = pow(sin(x * PI * 10 + t1), 2);
    double b = sin(x * PI * 6 - t2);
    double c = triangle((x * 3 + sin(t3)) / 2);
    double v = pow((a + b + c) / 3, 2);
    return hsv(.3, a, v);
}
