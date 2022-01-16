#include "ColorTwinkles.h"

ColorTwinkles::ColorTwinkles(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void ColorTwinkles::beforeRender() {
    t1 = int1.time(.5, state->linearFxSpeed) * TWO_PI;
    t2 = int2.time(.15, state->linearFxSpeed) * TWO_PI;
}

CRGB ColorTwinkles::render(int16_t index, double x) {
    double a = pow((1 + sin(index / 3 + TWO_PI * sin(index / 2 + t1))) / 2, 4) / 2;
    double b = sin(index / 3 + TWO_PI * sin(index / 2 + t2));
    return hsv(b, 1, a > .05 ? a : 0);
}
