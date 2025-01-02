#include "Traffic.h"

Traffic::Traffic(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    items = new HarmonicMotion[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].setup(strip);
    }
}

Traffic::~Traffic() {
    delete audioTrigger;
    delete[] items;
}

void Traffic::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].reset();
    }
    audioTrigger->reset();
}

void Traffic::loop() {
    strip->off();

    bool trigger = audioTrigger->triggered(.5);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger);
    }
}

void Traffic::loopItem(HarmonicMotion &item, bool &trigger) {
    item.loop();

    if (item.isStable() && trigger) {
        trigger = false; 
        resetItem(item);
    }
}

void Traffic::resetItem(HarmonicMotion &item) {
    uint8_t layer = random(LAYERS);
    double factor = pow(1 + 5 * (double(1 + layer) / (1 + LAYERS)), 2);
    double speed = factor * (5 + (15 + random(10)) * state->parabolicFxSpeed);

    item.reset()
        .setColor(ColorFromPalette(PALETTE, random8()));

    if (random(10) < 5) {
        item
            .setPosition(0)
            .setVelocity(speed)
            .setRange(-factor, 0)
            .setUpperBound(strip->last(), 0, HarmonicMotion::OUTSIDE);
    } else {
        item
            .setPosition(strip->last())
            .setVelocity(-speed)
            .setRange(0, factor)
            .setLowerBound(strip->first(), 0, HarmonicMotion::OUTSIDE);
    }
}
