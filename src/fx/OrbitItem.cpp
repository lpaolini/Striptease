#include "OrbitItem.h"

OrbitItem::OrbitItem() {};

void OrbitItem::setup(
    Strip *strip,
    State *state,
    uint8_t hue,
    float phase,
    float speed,
    float eccentricity,
    float eccentricityAngle
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
    float dT = timeElapsed / 1e6;
    timeElapsed = 0;
    float baseSpeed = DEG_TO_RAD * (MIN_SPEED + SPEED_FACTOR * state->linearFxSpeed);
    angle += dT * (baseSpeed + speed) * (1 + cosf(angle - eccentricityAngle) * eccentricity);
    float orbitX = (1 - cosf(angle)) / 2;
    float orbitY = (1 - sinf(angle)) / 2;
    uint8_t brightness = MIN_BRIGHTNESS + (255 - MIN_BRIGHTNESS) * orbitY;
    pixel.setNormalized(orbitX, CHSV(hue, 255, brightness));
}
