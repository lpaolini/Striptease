#include "Motion.h"

Motion::Motion(Strip *strip, AudioChannel *audioChannel, State *state, CRGB color, float velocityFactor, float accelerationFactor) : Fx(strip, audioChannel, state) {
    this->color = color;
    this->velocityFactor = velocityFactor;
    this->accelerationFactor = accelerationFactor;
    audioTrigger = new AudioTrigger(audioChannel);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.setup(strip);
    }
}

Motion::~Motion() {
    delete audioTrigger;
}

void Motion::reset() {
    clear();
    for (int i = 0; i < ITEMS; i++) {
        items[i].ball.reset();
    }
    fadeTimer.reset();
    inhibitTimer.reset();
}

void Motion::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    bool trigger = audioTrigger->triggered(3);

    if (trigger && items[nextItem].ball.isStable() && inhibitTimer.isElapsed()) {
        inhibitTimer.reset();
        resetItem(items[nextItem]);
        nextItem = (nextItem + 1) % ITEMS;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.loop();
    }
}

void Motion::resetItem(Item &item) {
    item.ball.reset()
        .setColor(color)
        .setVelocity(velocityFactor * state->linearFxSpeed)
        .setAcceleration(accelerationFactor * state->linearFxSpeed)
        .setPosition(0)
        .setUpperBound(strip->last());
}
