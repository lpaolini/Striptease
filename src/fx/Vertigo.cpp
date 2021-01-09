#include "Vertigo.h"

Vertigo::Vertigo(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.setup(strip);
    }
}

void Vertigo::reset() {
    clear(strip);
    for (int i = 0; i < ITEMS; i++) {
        items[i].ball.reset();
        items[i].timer = 0;
    }
    fadeTimer.reset();
    inhibitTimer.reset();
}

void Vertigo::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    bool signal = audioChannel->signalDetected;
    bool beat = audioChannel->beatDetected;
    bool trigger = (signal && beat) || (!signal && random8(100) == 0);

    if (trigger && items[nextItem].ball.isStable() && inhibitTimer.isElapsed()) {
        inhibitTimer.reset();
        randomizeItem(items[nextItem], beat ? audioChannel->rms : .1f);
        nextItem = (nextItem + 1) % ITEMS;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.loop();
    }
}

void Vertigo::randomizeItem(Item &item, float strength) {
    item.ball.reset()
        .setColor(CRGB::Blue)
        // .setAcceleration(100 + 1000 * state->linearFxSpeed)
        .setAcceleration(50, 0, 2000 * state->linearFxSpeed)
        .setPosition(0)
        .setUpperBound(strip->count - 1);
    item.timer = 0;
}
