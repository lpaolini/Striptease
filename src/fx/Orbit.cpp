#include "Orbit.h"

OrbitItem::OrbitItem() {};

void OrbitItem::setup(
    Strip *strip,
    State *state,
    uint8_t hue,
    double phase,
    double speed,
    double eccentricity,
    double eccentricityAngle
) {
    this->strip = strip;
    this->state = state;
    this->hue = hue;
    this->phase = DEG_TO_RAD * phase;
    this->speed = DEG_TO_RAD * speed;
    this->eccentricity = eccentricity;
    this->eccentricityAngle = DEG_TO_RAD * eccentricityAngle;
    pixel.setup(strip);
    reset();
}

void OrbitItem::reset() {
    angle = phase;
    pixel.reset();
    timeElapsed = 0;
}

void OrbitItem::loop() {
    double dT = timeElapsed / 1e6;
    timeElapsed = 0;
    double baseSpeed = DEG_TO_RAD * (MIN_SPEED + SPEED_FACTOR * state->linearFxSpeed);
    angle += dT * (baseSpeed + speed) * (1 + cosf(angle - eccentricityAngle) * eccentricity);
    double orbitX = (1 - cosf(angle)) / 2;
    double orbitY = (1 - sinf(angle)) / 2;
    uint8_t brightness = MIN_BRIGHTNESS + (255 - MIN_BRIGHTNESS) * orbitY;
    pixel.setNormalized(orbitX, CHSV(hue, 255, brightness));
}

Orbit::Orbit(Strip *strip, State *state, double phase) : Fx(strip, state) {
    this->phase = phase;
    for (uint8_t i = 0; i < ITEMS; i++) {
        item[i].setup(strip, state, HUE_STEP * i, phase + ANGLE_STEP * i, SPEED_STEP * i, ECCENTRICITY, ECCENTRICITY_ANGLE);
    }
    reset();
}

void Orbit::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        item[i].reset();
    }
    timer.reset();
}

void Orbit::loop() {
    if (timer.isElapsed()) {
        strip->fade(150);
        for (uint8_t i = 0; i < ITEMS; i++) {
            item[i].loop();
        }
    }
}
