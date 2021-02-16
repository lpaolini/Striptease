#include "Ripple.h"

Ripple::Ripple(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    items = new Item[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.setup(strip);
    }
}

Ripple::~Ripple() {
    delete audioTrigger;
    delete[] items;
}

void Ripple::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].ball.reset();
        items[i].timer = 0;
        items[i].decay = 0;
    }
    fadeTimer.reset();
    audioTrigger->reset();
}

void Ripple::loop() {
    strip->paint(BACKGROUND_COLOR, false);

    if (fadeTimer.isElapsed()) {
        for (uint8_t i = 0; i < ITEMS; i++) {
            fadeItem(items[i]);
        }
    }

    bool trigger = audioTrigger->triggered(2);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger, audioChannel->beatDetected ? audioChannel->rms : .1f);
    }
}

void Ripple::fadeItem(Item &item) {
    if (item.timer > DECAY_DELAY) {
        item.ball.color.fadeToBlackBy(item.decay);
    }
}

void Ripple::loopItem(Item &item, bool &trigger, float strength) {
    item.ball.loop();

    if (!item.ball.color && trigger) {
        trigger = false;
        randomizeItem(item, strength);
    }
}

void Ripple::randomizeItem(Item &item, float strength) {
    uint16_t pos = strip->random();
    uint8_t size = 5;
    item.ball.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setElasticConstant(random8(10) - 5)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(15 + 200 * state->parabolicFxSpeed * strength)
        .setRange(-size, size)
        .setMirror(true);
    item.timer = 0;
    item.decay = random8(2, 10);
}
