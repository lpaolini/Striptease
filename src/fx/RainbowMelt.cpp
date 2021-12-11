#include "RainbowMelt.h"

RainbowMelt::RainbowMelt(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void RainbowMelt::reset() {
    clear();
}

void RainbowMelt::loop() {
    strip->off();
    for (int16_t index = strip->first(); index < strip->last(); index++) {
        double x = double(index) / strip->last();
        double t1 = int1.time(.02 + .2 * (1 - state->linearFxSpeed));  // Time it takes for regions to move and melt 
        double c1 = 2 * abs(x - .5);  // 0 at strip endpoints, 1 in the middle
        double c2 = Interval::toWave(c1);
        double c3 = Interval::toWave(c2 + t1);
        double v = pow(Interval::toWave(c3 + t1), 2);  // Separate the colors with dark regions
        CRGB color = CHSV(255 * (c1 + t1), 255, 255 * v);
        strip->paint(index, color);
    }
}
