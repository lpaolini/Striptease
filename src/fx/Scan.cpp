#include "Scan.h"

Scan::Scan(Strip *strip, State *state) : Fx(strip, state) {
    item.setup(strip);
}

void Scan::reset() {
    item.reset()
        .setGradient(GRADIENT)
        .setPosition(strip->center())
        .setFixedPointPosition(strip->center())
        .setVelocity(strip->size() * (.25 + .5 * state->linearFxSpeed))
        .setRange(-strip->size() / 10, strip->size() / 10)
        .setLowerBound(strip->first(), -1, HarmonicMotion::INSIDE)
        .setUpperBound(strip->last(), -1, HarmonicMotion::INSIDE)
        .setShowWhenStable(true);
}

void Scan::loop() {
    clear();
    item.loop();
    strip->paint(strip->first(), CRGB::Gray, false);
    strip->paint(strip->last(), CRGB::Gray, false);
}
