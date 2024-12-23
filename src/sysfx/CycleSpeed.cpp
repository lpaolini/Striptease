#include "CycleSpeed.h"

CycleSpeed::CycleSpeed(Strip *strip, State *state) : Fx(strip, state) {
    slider.setup(strip);
    reset();
}

void CycleSpeed::reset() {
    slider.reset()
        .setColor(CHSV(0, 0, 128))
        .setElasticConstant(500)
        .setCriticalDamping()
        .setRange(-2, 2)
        .setPosition(strip->fromNormalizedPosition(state->linearCycleSpeed))
        .setFixedPointPosition(strip->fromNormalizedPosition(state->linearCycleSpeed))
        .setShowWhenStable(true);
}

void CycleSpeed::loop() {
    strip->paint(CHSV(0, 255, 75), false);
    slider
        .setFixedPointPosition(strip->fromNormalizedPosition(state->linearCycleSpeed))
        .loop();
}
