#include "HarmonicMotion.h"

HarmonicMotion::HarmonicMotion() {};

HarmonicMotion& HarmonicMotion::setup(Strip *strip) {
    this->strip = strip;
    return reset();
}

HarmonicMotion& HarmonicMotion::reset() {
    color = 0;
    a0 = 0;
    a1 = 0;
    a2 = 0;
    k = 0;
    b = 0;
    x = 0;
    x0 = 0;
    v = 0;
    start = 0;
    end = 0;
    mirror = false;
    fill = false;
    showWhenStable = false;
    overwrite = false;
    xPrev = 0;
    vPrev = 0;
    lowerLimit.x = -1e20;
    lowerLimit.r = 1;
    upperLimit.x = 1e20;
    upperLimit.r = 1;
    timeElapsed = 0;
    return *this;
}

HarmonicMotion& HarmonicMotion::setColor(CRGB color) {
    this->color = color;
    this->renderingMode = COLOR;
    return *this;
}

HarmonicMotion& HarmonicMotion::setGradient(Gradient *gradient) {
    this->gradient = gradient;
    this->renderingMode = GRADIENT;
    return *this;
}

HarmonicMotion& HarmonicMotion::setAcceleration(double a0, double a1, double a2) {
    this->a0 = a0;
    this->a1 = a1;
    this->a2 = a2;
    return *this;
}

HarmonicMotion& HarmonicMotion::setElasticConstant(double k) {
    this->k = k;
    return *this;
}

HarmonicMotion& HarmonicMotion::setDamping(double b) {
    this->b = b;
    return *this;
}

HarmonicMotion& HarmonicMotion::setCriticalDamping(double correctionFactor) {
    this->b = 2 * sqrtf(k) * correctionFactor;
    return *this;
}

HarmonicMotion& HarmonicMotion::setPosition(double x) {
    this->x = x;
    return *this;
}

HarmonicMotion& HarmonicMotion::setRandomPosition() {
    return setPosition(strip->random());
}

HarmonicMotion& HarmonicMotion::setVelocity(double v) {
    this->v = v;
    return *this;
}

HarmonicMotion& HarmonicMotion::setFixedPointPosition(double x0) {
    this->x0 = x0;
    return *this;
}

HarmonicMotion& HarmonicMotion::setRandomFixedPointPosition() {
    return setFixedPointPosition(strip->random());
}

HarmonicMotion& HarmonicMotion::setLowerBound(double x, double r, ReboundMode reboundMode) {
    lowerLimit.x = x;
    lowerLimit.r = r;
    lowerLimit.reboundMode = reboundMode;
    return *this;
}

HarmonicMotion& HarmonicMotion::setUpperBound(double x, double r, ReboundMode reboundMode) {
    upperLimit.x = x;
    upperLimit.r = r;
    upperLimit.reboundMode = reboundMode;
    return *this;
}

HarmonicMotion& HarmonicMotion::setRange(int start, int end) {
    this->start = start;
    this->end = end;
    return *this;
}

HarmonicMotion& HarmonicMotion::setMirror(bool mirror) {
    this->mirror = mirror;
    return *this;
}

HarmonicMotion& HarmonicMotion::setFill(bool fill) {
    this->fill = fill;
    return *this;
}

HarmonicMotion& HarmonicMotion::setShowWhenStable(bool showWhenStable) {
    this->showWhenStable = showWhenStable;
    return *this;
}

HarmonicMotion& HarmonicMotion::setOverwrite(bool overwrite) {
    this->overwrite = overwrite;
    return *this;
}

double HarmonicMotion::getFixedPointPosition() {
    return x0;
}

double HarmonicMotion::getPosition() {
    return x;
}

double HarmonicMotion::getVelocity() {
    return v;
}

double HarmonicMotion::getAcceleration() {
    return a0;
}

int HarmonicMotion::getLowerLimitCompensation() {
    switch (lowerLimit.reboundMode) {
        case INSIDE:
            return start;
        case OUTSIDE:
            return end + 1;
        default:
            return 0;
    }
}

int HarmonicMotion::getUpperLimitCompensation() {
    switch (upperLimit.reboundMode) {
        case INSIDE:
            return end;
        case OUTSIDE:
            return start - 1;
        default:
            return 0;
    }
}

bool HarmonicMotion::isLowerLimit() {
    double limit = lowerLimit.x - getLowerLimitCompensation();
    // if (x <= limit && v < 0) {
    if (x <= limit) {
        x = limit;
        return true;
    }
    return false;
}

bool HarmonicMotion::isUpperLimit() {
    double limit = upperLimit.x - getUpperLimitCompensation();
    // if (x >= limit && v > 0) {
    if (x >= limit) {
        x = limit;
        return true;
    }
    return false;
}

bool HarmonicMotion::isStable() {
    double force = a0 - (k * (x - x0));
    bool balanced = abs(force) < 1;
    bool bottom = force < 0 && isLowerLimit();
    bool top = force > 0 && isUpperLimit();
    return abs(v) < 1 && (balanced || bottom || top);
}

void HarmonicMotion::update() {
    xPrev = x;
    vPrev = v;
    double dT = timeElapsed / 1e6;
    timeElapsed = 0;
    a1 += a2 * dT;
    a0 += a1 * dT;
    v += (a0 - (k * (x - x0) + b * v)) * dT;
    x += v * dT;

    if (isLowerLimit()) {
        v *= lowerLimit.r;
    } else if (isUpperLimit()) {
        v *= upperLimit.r;
    } else if (isStable()) {
        v = 0;
    }
}

void HarmonicMotion::loop() {
    update();
    if (renderingMode && (!isStable() || showWhenStable)) {
        show(false);
        if (mirror) {
            show(true);
        }
    }
}

void HarmonicMotion::show(bool mirrored) {
    if (mirrored) {
        double pos1 = round(2 * x0 - x);
        double pos2 = round(fill ? x0 : 2 * x0 - xPrev);
        double posMin = min(pos1, pos2) - end;
        double posMax = max(pos1, pos2) - start;
        render(posMin, posMax);
    } else {
        double pos1 = round(x);
        double pos2 = round(fill ? x0 : xPrev);
        double posMin = min(pos1, pos2) + start;
        double posMax = max(pos1, pos2) + end;
        render(posMin, posMax);
    }
}

void HarmonicMotion::render(double posMin, double posMax) {
    switch (renderingMode) {
    case COLOR:
        strip->paint(posMin, posMax, color, !overwrite);
        break;
    case GRADIENT:
        strip->paint(posMin, posMax, gradient, 0, 1, !overwrite);
        break;
    default:
        break;
    }
}
