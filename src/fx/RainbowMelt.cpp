#include "RainbowMelt.h"

RainbowMelt::RainbowMelt(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void RainbowMelt::beforeRender() {
    t1 = int1.time(.02, state->linearFxSpeed);  // Time it takes for regions to move and melt 
}

CRGB RainbowMelt::render(int16_t index, double x) {
    double c1 = 2 * abs(x - .5);  // 0 at strip endpoints, 1 in the middle
    double c2 = wave(c1);
    double c3 = wave(c2 + t1);
    double v = pow(wave(c3 + t1), 2);  // Separate the colors with dark regions
    return hsv(c1 + t1, 1, v);
}
