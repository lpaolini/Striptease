#include "RippleReflections.h"

RippleReflections::RippleReflections(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void RippleReflections::reset() {
    clear();
}

void RippleReflections::loop() {
    strip->off();
    double t1 = TWO_PI * int1.time(.03);
    double t2 = TWO_PI * int2.time(.05);
    double t3 = TWO_PI * int3.time(.04);
    for (int16_t index = strip->first(); index < strip->last(); index++) {
        double x = double(index) / strip->size();
        double a = pow(sin(x * PI * 10 + t1), 2);
        double b = sin(x * PI * 6 - t2);
        double c = Interval::toTriangle((x * 3 + sin(t3)) / 2);
        double v = pow((a + b + c) / 3, 2);
        CRGB color = CHSV(.3 * 255, a * 255, v * 255);
        strip->paint(index, color);
    }
}
