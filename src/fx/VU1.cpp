#include "VU1.h"

VU1::VU1(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    vu.setup(strip);
    peak.setup(strip);
    peakHold.setup(strip);
    reset();
}

void VU1::reset() {
    clear();
    resetVU();
    resetPeak();
    resetPeakHold();
    fadeTimer.reset();
}

void VU1::resetVU() {
    vu.reset()
        .setColor(CRGB::Blue)
        .setElasticConstant(100)
        .setCriticalDamping()
        .setRange(1, 5)
        .setLowerBound(0)
        .setShowWhenStable(true);
}

void VU1::resetPeak() {
    peak.reset()
        .setColor(CRGB(0, 0, 8))
        .setFill(true)
        .setLowerBound(0)
        .setShowWhenStable(true);
}

void VU1::resetPeakHold() {
    peakHold.reset()
        .setColor(CRGB::Red)
        .setRange(1, 5)
        .setLowerBound(0)
        .setShowWhenStable(true);
}

void VU1::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(100);
    }

    vu
        .setFixedPointPosition(strip->fromNormalizedPosition(audioChannel->peak))
        .loop();

    peak
        .setPosition(max(peak.getPosition(), strip->fromNormalizedPosition(audioChannel->peakSmooth)))
        .setVelocity(-1000 * (.1 + .9 * state->linearFxSpeed))
        .loop();

    peakHold
        .setPosition(max(peakHold.getPosition(), strip->fromNormalizedPosition(audioChannel->peakSmooth)))
        .setVelocity(-100 * (.1 + .9 * state->linearFxSpeed))
        .loop();
}
