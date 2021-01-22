#include "Volcane.h"

Volcane::Volcane(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item *item = new Item();
        item->head->setup(strip);
        item->tail->setup(strip);
        items[i] = item;
    }
}

void Volcane::reset() {
    clear(strip);
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i]->head->reset();
        items[i]->tail->reset();
    }
}

void Volcane::restart(Item *item) {
    float g = -2500 * state->parabolicFxSpeed;
    float v0 = sqrtf(g * -2 * random8(70, 100) / 100 * strip->last());
    item->head->reset()
        .setColor(CRGB::Red)
        .setAcceleration(g)
        .setVelocity(v0)
        .setRange(-2, 2)
        .setLowerBound(-10);

    item->tail->reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setPosition(0)
        .setElasticConstant(1000 * state->parabolicFxSpeed)
        .setCriticalDamping()
        .setFill(true)
        .setLowerBound(0);
}

void Volcane::loop() {
    strip->off();
    bool trigger = audioChannel->trigger(3);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item *item = items[i];
        if (trigger && item->tail->isStable()) {
            restart(item);
            trigger = false;
        }
        item->head->loop();
        item->tail->setFixedPointPosition(item->head->getPosition());
        item->tail->loop();
    }
}
