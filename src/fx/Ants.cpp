#include "Ants.h"

Ants::Ants(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    items = new Item[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].item.setup(strip);
    }
}

Ants::~Ants() {
    delete[] items;
}

void Ants::reset() {
    clear(strip);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].item.reset();
    }
}

void Ants::loop() {
    strip->off();

    bool signal = audioChannel->signalDetected;
    bool beat = audioChannel->beatDetected;
    bool trigger = (signal && beat) || (!signal && random8(100) == 0);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger, beat ? audioChannel->rms : .1f);
    }
}

void Ants::loopItem(Item &item, bool &trigger, float strength) {
    item.item.loop();
    if (item.item.getVelocity() < 0) {
        item.item.color.fadeToBlackBy(item.decay);
    }

    if (item.item.isStable() && trigger) {
        trigger = false; 
        randomizeItem(item, strength);
    }
}

void Ants::randomizeItem(Item &item, float strength) {
    item.item.reset()
        .setColor(ColorFromPalette(PALETTE, state->slowRotatingHue))
        .setPosition(0)
        .setVelocity(100 + 200 * state->parabolicFxSpeed)
        .setLowerBound(0, 0, 1)
        .setUpperBound(strip->last(), -1, 1)
        .setRange(0, 5);
    item.decay = 5;
}
