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

    bool trigger = audioChannel->trigger(1);

    float translationY = SPEED * dT;
    float rotation = 0;

    if (transition == 1) {
        if (timer.isElapsed()) {
            switch (random(5)) {
                case 1:
                    steeringAngle = -random(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = .001 * random(MIN_TRANSITION_SPEED, MAX_TRANSITION_SPEED);
                    transition = 0;
                    break;
                case 2:
                    steeringAngle = random(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = .001 * random(MIN_TRANSITION_SPEED, MAX_TRANSITION_SPEED);
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
        rotation = steeringAngle * Easing::deltaEaseInOutCubic(transition, previousTransition) / 180 * TWO_PI;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], translationY, rotation, trigger);
    }
}

void DeepSpace::loopItem(Item &item, float translationY, float rotation, bool &trigger) {
    item.point.translate(0, translationY).rotate(rotation);

    if (item.point.y < 0) {
        randomizeItem(item);
    } 

    float angle = item.point.angle();
    float distance = item.point.radius();
    float distanceSquared = pow(distance, 2);

    float pos = min(max(0, 1 - (angle / PI)), 1);
    uint8_t brightness = min(255, 5 * MAX_SQUARED_DISTANCE / distanceSquared);

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
    item.point = Point::fromPolar(distance, angle);
    item.type = random(100) < (5 + 95 * state->parabolicFxSpeed)
        ? BLUE
        : HIDDEN;
    item.pixel.reset();
}
