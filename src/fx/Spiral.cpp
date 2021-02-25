#include "Spiral.h"

Spiral::Spiral(Strip *strip, State *state, uint16_t count, float turns, float eccentricity) : Fx(strip, state) {
    this->count = count;
    this->turns = turns;
    this->eccentricity = eccentricity;
    items = new EllipticMotion[count];
    for (uint16_t i = 0; i < count; i++) {
        items[i].setup(strip);
    }
}

void Spiral::reset() {
    clear();
    for (uint16_t i = 0; i < count; i++) {
        items[i].reset()
            // .setCenter(.5 + float(random(-50, 50)) / 100)
            .setCenter(.5)
            .setRadius(.5 / count * (i + 1))
            .setAngle(turns * 2 * PI / count * i)
            .setEccentricity(eccentricity)
            .setEccentricityAngle(-HALF_PI)
            .setHue(160)
            .setAngularSpeed(0);
    }
    fadeTimer.reset();
}

void Spiral::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(100);
    }
    for (uint16_t i = 0; i < count; i++) {
        items[i]
            .setAngularSpeed(DEG_TO_RAD * (MIN_ANGULAR_SPEED + (MAX_ANGULAR_SPEED - MIN_ANGULAR_SPEED) * state->linearFxSpeed))
            .loop();
    }
}
