#include "DeepSpace.h"

DeepSpace::DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].pixel.setup(strip);
    }
}

void DeepSpace::reset() {
    clear(strip);
    for (uint8_t i = 0; i < ITEMS; i++) {
        randomizeItem(items[i]);
    }
    time = 0;
    steeringAngle = 0;
    transition = 1;
    timer.reset();
}

void DeepSpace::loop() {
    strip->off();

    float dT = time / 1e6;
    time = 0;

    bool trigger = audioChannel->signalDetected
        ? audioChannel->beatDetected
        : random8() == 0;

    float rotationAngle = 0;

    if (transition == 1) {
        if (timer.isElapsed()) {
            switch (random(5)) {
                case 1:
                    steeringAngle = -random(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = -.001 * random(1, 5) * steeringAngle;
                    transition = 0;
                    break;
                case 2:
                    steeringAngle = random(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = .001 * random(1, 5) * steeringAngle;
                    transition = 0;
                    break;
                default:
                    steeringAngle = 0;
                    transitionSpeed = 0;
                    break;
            }
            timer.reset();
        }
    } else {
        float previousTransition = transition;
        transition = min(1, transition + transitionSpeed * dT);
        rotationAngle = steeringAngle * deltaEaseInOutSine(transition, previousTransition) / 180 * TWO_PI;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        moveItem(items[i], speed * dT);
        rotateItem(items[i], rotationAngle);
        loopItem(items[i], dT, trigger);
    }
}

float DeepSpace::deltaEaseInOutSine(float x1, float x0) {
    return (cos(PI * x0) - cos(PI * x1)) / 2;
}

void DeepSpace::rotateItem(Item &item, float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    item.x = item.x * cosTheta - item.y * sinTheta;
    item.y = item.x * sinTheta + item.y * cosTheta;
}

void DeepSpace::moveItem(Item &item, float distance) {
    item.y -= distance;
}

void DeepSpace::loopItem(Item &item, float dT, bool &trigger) {
    if (item.y < 0) {
        randomizeItem(item);
    } 

    float angle = atan2f(item.y, item.x);
    float distanceSquared = powf(item.x, 2) + powf(item.y, 2);
    float distance = sqrt(distanceSquared);
    float pos = min(max(0, 1 - (angle / PI)), 1);
    uint8_t brightness = min(255, 5 * MAX_SQUARE_DISTANCE / distanceSquared);

    if (trigger && item.type == BLUE && distance < MAX_MUTATION_DISTANCE) {
        trigger = false;
        item.type = RED;
    }

    CRGB color;
    switch (item.type) {
        case BLUE:
            color = CHSV(160, 255, brightness);
            break;
        case RED:
            color = CHSV(0, 255, brightness);
            break;
        default:
            color = CRGB::Black;
            break;
    }

    item.pixel.setNormalized(pos, color);
}

void DeepSpace::randomizeItem(Item &item) {
    long distance = random(MIN_DISTANCE, MAX_DISTANCE);
    float angle = random(0, 18000) / (100 * PI);
    item.x = distance * cosf(angle);
    item.y = distance * sinf(angle);
    item.type = random(100) < 100 * state->parabolicFxSpeed 
        ? BLUE
        : HIDDEN;
    item.pixel.reset();
}
