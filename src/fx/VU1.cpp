#include "VU1.h"

VU1::VU1(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    peak.setup(strip);
    peakHold.setup(strip);
    reset();
}

void VU1::reset() {
    clear();
    resetPeak();
    resetPeakHold();
    fadeTimer.reset();
}

void VU1::resetPeak() {
    peak.reset()
        .setColor(CRGB::Blue)
        .setElasticConstant(100)
        .setDamping(5)
        .setLowerBound(0)
        .setShowWhenStable(true);
}

void VU1::resetPeakHold() {
    peakHold.reset()
        .setColor(CRGB::Red)
        .setShowWhenStable(true)
        .setRange(1, 5)
        .setLowerBound(0);
}

void VU1::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(100);
    }

    peak
        .setFixedPointPosition(strip->fromNormalizedPosition(audioChannel->peak))
        .loop();

    peakHold
        .setPosition(strip->fromNormalizedPosition(audioChannel->peakSmooth))
        .setVelocity(-10)
        .loop();
}
