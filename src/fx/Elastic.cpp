#include "Elastic.h"

Elastic::Elastic(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].setup(strip);
    }
}

void Elastic::reset() {
    clear(strip);
    for (int i = 0; i < ITEMS; i++) {
        items[i].reset();
    }
    fadeTimer.reset();
}

void Elastic::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    bool signal = audioChannel->signalDetected;
    bool beat = audioChannel->beatDetected;
    bool trigger = (signal && beat) || (!signal && random8(100) == 0);

    if (trigger) {
        clear(strip);
        randomizeItem(items[nextItem], beat ? audioChannel->rms : .1f);
        nextItem = (nextItem + 1) % ITEMS;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].loop();
    }
}

void Elastic::randomizeItem(HarmonicMotion &item, float strength) {
    uint16_t pos = strip->randomPosExclude(item.getPosition(), 0);
    item.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setElasticConstant(20)
        .setCriticalDamping()
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(50 + random16(400 * state->linearFxSpeed))
        .setMirror(true)
        .setFill(true);
}
