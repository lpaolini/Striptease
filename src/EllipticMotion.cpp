#include "EllipticMotion.h"

EllipticMotion::EllipticMotion() {};

EllipticMotion& EllipticMotion::setup(Strip *strip) {
    this->strip = strip;
    pixel.setup(strip);
    return reset();
}

EllipticMotion& EllipticMotion::reset() {
    hue = 0;
    saturation = 255;
    center = 0;
    radius = 0;
    angle = 0;
    angularSpeed = 0;
    eccentricity = 0;
    eccentricityAngle = 0;
    timeElapsed = 0;
    return *this;
}

EllipticMotion& EllipticMotion::setHue(uint8_t hue) {
    this->hue = hue;
    return *this;
}

EllipticMotion& EllipticMotion::setSaturation(uint8_t saturation) {
    this->saturation = saturation;
    return *this;
}

EllipticMotion& EllipticMotion::setCenter(double center) {
    this->center = center;
    return *this;    
}

EllipticMotion& EllipticMotion::setRadius(double radius) {
    this->radius = radius;
    return *this;    
}

EllipticMotion& EllipticMotion::setAngle(double angle) {
    this->angle = angle;
    return *this;    
}

EllipticMotion& EllipticMotion::setAngularSpeed(double angularSpeed) {
    this->angularSpeed = angularSpeed;
    return *this;    
}

EllipticMotion& EllipticMotion::setEccentricity(double eccentricity) {
    this->eccentricity = eccentricity;
    return *this;    
}

EllipticMotion& EllipticMotion::setEccentricityAngle(double eccentricityAngle) {
    this->eccentricityAngle = eccentricityAngle;
    return *this;    
}

EllipticMotion& EllipticMotion::setOverwrite(bool overwrite) {
    this->overwrite = overwrite;
    return *this;    
}

void EllipticMotion::loop() {
    double dT = timeElapsed / 1e6;
    timeElapsed = 0;

    double eccentricCompensation = (1 + cos(angle - eccentricityAngle) * eccentricity);
    angle += angularSpeed * dT * eccentricCompensation;

    double x = center + radius * cos(angle);
    uint8_t brightness = MIN_BRIGHTNESS + (255 - MIN_BRIGHTNESS) * (sin(angle) + 1) / 2;

    pixel.setNormalized(x, CHSV(hue, saturation, brightness));
}
