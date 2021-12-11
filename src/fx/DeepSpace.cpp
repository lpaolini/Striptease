#include "DeepSpace.h"

DeepSpace::DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state, CRGB baseColor, CRGB accentColor) : Fx(strip, audioChannel, state) {
    this->baseColor = baseColor;
    this->accentColor = accentColor;
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

    double dT = time / 1e6;
    time = 0;

    bool trigger = audioTrigger->triggered(1);

    double translationY = SPEED * dT;
    double rotation = 0;

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
        double previousTransition = transition;
        transition = min(1, transition + transitionSpeed * dT);
        rotation = steeringAngle * Easing::deltaEaseInOutCubic(transition, previousTransition) / 180 * TWO_PI;
    }

    for (uint16_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], translationY, rotation, trigger);
    }
}

void DeepSpace::loopItem(Item &item, double translationY, double rotation, bool &trigger) {
    item.point.translate(0, translationY).rotate(rotation);

    if (item.point.y <= 0) {
        randomizeItem(item);
    } 

    double angle = item.point.angle();
    double distance = item.point.radius();
    double distanceSquared = pow(distance, 2);

    // double pos = min(1, max(0, 1 - (angle / PI)));
    double pos = 1 - (angle / PI);
    uint8_t brightness = min(255, 5 * MAX_SQUARED_DISTANCE / distanceSquared);

    if (trigger && item.type == NORMAL && distance < MAX_MUTATION_DISTANCE) {
        trigger = false;
        item.type = HIGHLIGHT;
    }

    CRGB color;
    switch (item.type) {
        case NORMAL:
            color = CRGB(baseColor).fadeToBlackBy(255 - brightness);
            break;
        case HIGHLIGHT:
            color = CRGB(accentColor).fadeToBlackBy(255 - brightness);
            break;
        default:
            color = CRGB::Black;
            break;
    }

    item.pixel.setNormalized(pos, color);
}

void DeepSpace::randomizeItem(Item &item) {
    double distance = random16(MIN_DISTANCE, MAX_DISTANCE);
    double angle = random16(0, 18000) / (100 * PI);
    item.point = Point::fromPolar(distance, angle);
    item.type = random8(100) < (state->parabolicFxSpeed * 95 + 5)
        ? NORMAL
        : HIDDEN;
    item.pixel.reset();
}
