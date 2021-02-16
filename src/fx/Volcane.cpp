#include "Volcane.h"

Volcane::Volcane(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item *item = &items[i];
        item->head.setup(strip);
        item->tail.setup(strip);
    }
}

Volcane::~Volcane() {
    delete audioTrigger;
}

void Volcane::reset() {
    clear();
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item *item = &items[i];
        item->head.reset();
        item->tail.reset();
    }
    audioTrigger->reset();
}

void Volcane::restart(Item *item) {
    float g = -2500 * state->parabolicFxSpeed;
    float v0 = sqrtf(g * -2 * random8(70, 100) / 100 * strip->last());
    item->head.reset()
        .setColor(CRGB::Red)
        .setAcceleration(g)
        .setVelocity(v0)
        .setRange(-2, 2)
        .setLowerBound(-10);

    item->tail.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setPosition(0)
        .setElasticConstant(1000 * state->parabolicFxSpeed)
        .setCriticalDamping()
        .setFill(true)
        .setLowerBound(0);
}

void Volcane::loop() {
    strip->off();
    bool trigger = audioTrigger->triggered(1);
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        Item *item = &items[i];
        if (trigger && item->tail.isStable()) {
            restart(item);
            trigger = false;
        }
        item->head.loop();
        item->tail.setFixedPointPosition(item->head.getPosition());
        item->tail.loop();
    }
}
