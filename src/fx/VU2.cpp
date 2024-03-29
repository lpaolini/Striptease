#include "VU2.h"

VU2::VU2(Strip *strip, AudioChannel *audioChannel, uint16_t size, double elasticConstant, CRGB color) : Fx(strip, audioChannel) {
    this->size = size;
    this->elasticConstant = elasticConstant;
    this->color = color;
    peak.setup(strip);
    reset();
}

void VU2::reset() {
    clear();
    resetPeak();
}

void VU2::resetPeak() {
    peak.reset()
        .setColor(color)
        .setElasticConstant(elasticConstant)
        .setCriticalDamping()
        .setLowerBound(0)
        .setRange(0, max(0, size - 1))
        .setPosition(strip->fromNormalizedPosition(audioChannel->peakSmooth))
        .setShowWhenStable(false);
}

void VU2::loop() {
    strip->fade(20);
    peak
        .setFixedPointPosition(strip->fromNormalizedPosition(audioChannel->peakSmooth))
        .loop();
}
