#include "Ants.h"

Ants::Ants(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    items = new Item[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].item.setup(strip);
    }
}

Ants::~Ants() {
    delete audioTrigger;
    delete[] items;
}

void Ants::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].item.reset();
    }
    audioTrigger->reset();
}

void Ants::loop() {
    strip->off();

    bool trigger = audioTrigger->triggered(.5);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger);
    }
}

void Ants::loopItem(Item &item, bool &trigger) {
    item.item.loop();
    if (item.item.getVelocity() < 0) {
        item.item.color.fadeToBlackBy(item.decay);
    }

    if (item.item.isStable() && trigger) {
        trigger = false; 
        resetItem(item);
    }
}

void Ants::resetItem(Item &item) {
    item.item.reset()
        .setColor(ColorFromPalette(PALETTE, state->slowRotatingHue))
        .setPosition(0)
        .setVelocity(100 + 200 * state->parabolicFxSpeed)
        .setLowerBound(0, 0, 1)
        .setUpperBound(strip->last(), -1, 1)
        .setRange(0, 5);
    item.decay = 5;
}
