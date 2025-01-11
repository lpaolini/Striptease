#include "Sunset.h"

Sunset::Sunset(Strip *strip, State *state) : Fx(strip, state) {
    item.setup(strip);
}

void Sunset::reset() {
    item.reset()
        .setGradient(GRADIENT)
        .setElasticConstant(1)
        .setPosition(strip->center())
        .setFixedPointPosition(strip->center())
        .setVelocity(strip->size() * (.25 + .5 * state->linearFxSpeed))
        .setRange(-strip->size() / 4, strip->size() / 4)
        .setMirror(false)
        .setShowWhenStable(true);
}

void Sunset::loop() {
    clear();
    item.loop();
}
