#include "RippleReflections.h"

RippleReflections::RippleReflections(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void RippleReflections::reset() {
    clear();
}

void RippleReflections::loop() {
    strip->off();
    float t1 = TWO_PI * int1.time(.03);
    float t2 = TWO_PI * int2.time(.05);
    float t3 = TWO_PI * int3.time(.04);
    for (int16_t index = strip->first(); index < strip->last(); index++) {
        float x = float(index) / strip->size();
        float a = pow(sin(x * PI * 10 + t1), 2);
        float b = sin(x * PI * 6 - t2);
        float c = Interval::toTriangle((x * 3 + sin(t3)) / 2);
        float v = pow((a + b + c) / 3, 2);
        CRGB color = CHSV(.3 * 255, a * 255, v * 255);
        strip->paint(index, color);
    }
}
