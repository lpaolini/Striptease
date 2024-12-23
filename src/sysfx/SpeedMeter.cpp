#include "SpeedMeter.h"

SpeedMeter::SpeedMeter(Strip *strip, State *state) : Fx(strip, state) {
    slider.setup(strip);
    reset();
}

void SpeedMeter::reset() {
    slider.reset()
        .setColor(CHSV(0, 0, 128))
        .setElasticConstant(500)
        .setCriticalDamping()
        .setRange(-2, 2)
        .setPosition(strip->fromNormalizedPosition(state->linearFxSpeed))
        .setFixedPointPosition(strip->fromNormalizedPosition(state->linearFxSpeed))
        .setShowWhenStable(true);
}

void SpeedMeter::loop() {
    strip->paint(CHSV(160, 255, 50), false);
    slider
        .setFixedPointPosition(strip->fromNormalizedPosition(state->linearFxSpeed))
        .loop();
}
