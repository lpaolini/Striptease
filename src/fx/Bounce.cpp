#include "Bounce.h"

Bounce::Bounce(Strip *strip, State *state, uint16_t count, uint16_t size) : Fx(strip, state) {
    this->count = count;
    this->size = size;
    items = new HarmonicMotion[count];
    for (uint8_t i = 0; i < count; i++) {
        items[i].setup(strip);
        resetItem(items[i]);
    }
}

Bounce::~Bounce() {
    delete[] items;
}

void Bounce::reset() {
    clear();
    for (uint8_t i = 0; i < count; i++) {
        resetItem(items[i]);
    }
}

void Bounce::loop() {
    strip->off();
    for (uint8_t i = 0; i < count; i++) {
        loopItem(items[i]);
    }
}

void Bounce::loopItem(HarmonicMotion &item) {
    item.loop();

    if (item.isStable()) {
        resetItem(item);
    }
}

void Bounce::resetItem(HarmonicMotion &item) {
    item.reset()
        .setColor(ColorFromPalette(PALETTE, state->slowRotatingHue))
        .setRandomPosition()
        .setVelocity(random(100) + 200 * state->parabolicFxSpeed)
        .setDamping(state->linearFxSpeed)
        .setLowerBound(0, -1, 1)
        .setUpperBound(strip->last(), -1, 1)
        .setRange(0, size);
}
