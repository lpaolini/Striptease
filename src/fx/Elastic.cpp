#include "Elastic.h"

Elastic::Elastic(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].setup(strip);
    }
}

Elastic::~Elastic() {
    delete audioTrigger;
}

void Elastic::reset() {
    clear();
    for (int i = 0; i < ITEMS; i++) {
        items[i].reset();
    }
    fadeTimer.reset();
    audioTrigger->reset();
}

void Elastic::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    bool trigger = audioTrigger->triggered(1);

    if (trigger) {
        clear();
        randomizeItem(items[nextItem], audioChannel->beatDetected ? audioChannel->rms : .1f);
        nextItem = (nextItem + 1) % ITEMS;
    }

    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].loop();
    }
}

void Elastic::randomizeItem(HarmonicMotion &item, double strength) {
    uint16_t pos = strip->randomExclude(item.getPosition(), strip->size() / 5);
    item.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setElasticConstant(20)
        .setCriticalDamping(.5)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(random16(100 + 200 * state->linearFxSpeed, 250 + 500 * state->linearFxSpeed))
        .setMirror(true)
        .setFill(true);
}
