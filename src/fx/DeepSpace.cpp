#include "DeepSpace.h"

DeepSpace::DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    this->audioTrigger = new AudioTrigger(audioChannel);
    for (uint16_t i = 0; i < ITEMS; i++) {
        items[i].pixel.setup(strip);
    }
}

DeepSpace::~DeepSpace() {
    delete audioTrigger;
}

void DeepSpace::reset() {
    clear();
    for (uint16_t i = 0; i < ITEMS; i++) {
        randomizeItem(items[i]);
    }
    time = 0;
    steeringAngle = 0;
    transition = 1;
    timer.reset();
    audioTrigger->reset();
}

void DeepSpace::loop() {
    strip->off();

    float dT = time / 1e6;
    time = 0;

    bool trigger = audioTrigger->triggered(1);

    float translationY = SPEED * dT;
    float rotation = 0;

    if (transition == 1) {
        if (timer.isElapsed()) {
            switch (random8(5)) {
                case 1:
                    steeringAngle = -random16(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = .001 * random16(MIN_TRANSITION_SPEED, MAX_TRANSITION_SPEED);
                    transition = 0;
                    break;
                case 2:
                    steeringAngle = random16(MIN_STEERING, MAX_STEERING);
                    transitionSpeed = .001 * random16(MIN_TRANSITION_SPEED, MAX_TRANSITION_SPEED);
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

    for (uint16_t i = 0; i < ITEMS; i++) {
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

    if (trigger && item.type == NORMAL && distance < MAX_MUTATION_DISTANCE) {
        trigger = false;
        item.type = HIGHLIGHT;
    }

    CRGB color;
    switch (item.type) {
        case NORMAL:
            color = CHSV(160, 255, brightness);
            break;
        case HIGHLIGHT:
            color = CHSV(0, 255, brightness);
            break;
        default:
            color = CRGB::Black;
            break;
    }

    item.pixel.setNormalized(pos, color);
}

void DeepSpace::randomizeItem(Item &item) {
    float distance = random16(MIN_DISTANCE, MAX_DISTANCE);
    float angle = random16(0, 18000) / (100 * PI);
    item.point = Point::fromPolar(distance, angle);
    item.type = random8(100) < (state->parabolicFxSpeed * 95 + 5)
        ? NORMAL
        : HIDDEN;
    item.pixel.reset();
}
