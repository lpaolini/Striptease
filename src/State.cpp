#include "State.h"

State::State() {
    slowRotatingHue = random8();
    fastRotatingHue = random8();
    setFxSpeed(DEFAULT_FX_SPEED);
    setCycleSpeed(DEFAULT_CYCLE_SPEED);
}

void State::setup() {}

void State::setFxSpeed(uint8_t speed) {
    fxSpeed = speed;
    linearFxSpeed = float(fxSpeed) / 100;
    parabolicFxSpeed = pow(linearFxSpeed, 2);
}

uint8_t State::getFxSpeed() {
    return fxSpeed;
}

void State::decreaseFxSpeed() {
    setFxSpeed(max(fxSpeed - 5, 0));
}

void State::increaseFxSpeed() {
    setFxSpeed(min(fxSpeed + 5, 100));
}

void State::setCycleSpeed(uint8_t speed) {
    cycleSpeed = speed;
    linearCycleSpeed = float(cycleSpeed) / 100;
}

uint8_t State::getCycleSpeed() {
    return cycleSpeed;
}

void State::decreaseCycleSpeed() {
    setCycleSpeed(max(cycleSpeed - 5, 0));
}

void State::increaseCycleSpeed() {
    setCycleSpeed(min(cycleSpeed + 5, 100));
}

void State::loop() {
    float increase = 100 * parabolicFxSpeed * microseconds / 1e6;
    microseconds = 0;
    ((slowRotatingHueInternal += increase) >= 256) && (slowRotatingHueInternal -= 256);
    ((fastRotatingHueInternal += 10 * increase) >= 256) && (fastRotatingHueInternal -= 256);
    slowRotatingHue = floor(slowRotatingHueInternal);
    fastRotatingHue = floor(fastRotatingHueInternal);
}
