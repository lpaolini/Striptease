#include "Fireworks.h"

Fireworks::Fireworks(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.setup(strip);
    }
}

void Fireworks::reset() {
    clear(strip);
    for (int i = 0; i < ITEMS; i++) {
        items[i].ball.reset();
        items[i].timer = 0;
        items[i].decay = DECAY_RATE;
    }
    fadeTimer.reset();
    inhibitTimer.reset();
}

void Fireworks::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
        for (uint8_t i = 0; i < ITEMS; i++) {
            if (items[i].timer > DECAY_DELAY) {
                items[i].ball.color.fadeToBlackBy(items[i].decay);
            }
        }
    }

    bool trigger = audioChannel->trigger(5);

    if (trigger && items[nextItem].ball.isStable() && inhibitTimer.isElapsed()) {
        inhibitTimer.reset();
        randomizeItem(items[nextItem], audioChannel->beatDetected ? audioChannel->rms : .1f);
        nextItem = (nextItem + 1) % ITEMS;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.loop();
    }
}

void Fireworks::randomizeItem(Item &item, float strength) {
    uint16_t pos = strip->randomInRange(.25, .75);
    item.ball.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setDamping(2)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(50 + random16(100 * state->linearFxSpeed))
        .setMirror(true)
        ;
    item.timer = 0;
}
