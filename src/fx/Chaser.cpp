#include "Chaser.h"

Chaser::Chaser(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].setup(strip);
    }
}

Chaser::~Chaser() {
    delete audioTrigger;
}

void Chaser::reset() {
    clear();
    for (int i = 0; i < ITEMS; i++) {
        uint8_t size = random8(2, 5);
        items[i].reset()
            .setColor(ColorFromPalette(PALETTE, random8()))
            .setElasticConstant(4)
            .setCriticalDamping()
            .setFixedPointPosition(strip->random())
            .setVelocity(10)
            .setRange(-size, size)
            .setMirror(false)
            .setShowWhenStable(true);
    }
    moveTimer.reset();
    fadeTimer.reset();
    audioTrigger->reset();
}

void Chaser::loop() {
    if (fadeTimer.isElapsed()) {
        strip->fade(FADE_RATE);
    }

    if (audioTrigger->triggered(1)) {
        if (moveTimer.isElapsed()) {
            items[0].setFixedPointPosition(strip->randomExclude(items[0].getPosition(), 5));
        }
    }
    
    for (int i = 1; i < ITEMS; i++) {
        items[i].setFixedPointPosition(items[i - 1].getPosition());
    }

    for (int i = 0; i < ITEMS; i++) {
        items[i]
            .setElasticConstant(5 + 100 * state->parabolicFxSpeed)
            .setCriticalDamping()
            .loop();
    }
}
