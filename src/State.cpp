#include "State.h"

State::State() {
    rotatingHue = 0;
    setFxSpeed(DEFAULT_FX_SPEED);
    setCycleSpeed(DEFAULT_CYCLE_SPEED);
}

void State::setup() {}

void State::setFxSpeed(uint8_t speed) {
    fxSpeed = speed;
    linearFxSpeed = double(fxSpeed) / 100;
    parabolicFxSpeed = pow(linearFxSpeed, 2);
}

uint8_t State::getFxSpeed() {
    return fxSpeed;
}

void State::decreaseFxSpeed() {
    setFxSpeed(max(fxSpeed - 2, 0));
}

void State::increaseFxSpeed() {
    setFxSpeed(min(fxSpeed + 2, 100));
}

void State::setCycleSpeed(uint8_t speed) {
    cycleSpeed = speed;
    linearCycleSpeed = double(cycleSpeed) / 100;
}

uint8_t State::getCycleSpeed() {
    return cycleSpeed;
}

void State::decreaseCycleSpeed() {
    setCycleSpeed(max(cycleSpeed - 2, 0));
}

void State::increaseCycleSpeed() {
    setCycleSpeed(min(cycleSpeed + 2, 100));
}

void State::loop() {
    double increase = .0001 * parabolicFxSpeed * microseconds;
    microseconds = 0;
    rotatingHueInternal = fmod(rotatingHueInternal + increase, 256);
    rotatingHue = uint8_t(rotatingHueInternal);
}
