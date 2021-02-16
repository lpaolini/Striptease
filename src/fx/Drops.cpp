#include "Drops.h"

Drops::Drops(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    items = new Item[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].center.setup(strip);
        items[i].sides.setup(strip);
    }
}

Drops::~Drops() {
    delete audioTrigger;
    delete[] items;
}

void Drops::reset() {
    clear();
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].center.reset();
        items[i].sides.reset();
    }
}

void Drops::loop() {
    strip->paint(BACKGROUND_COLOR);

    bool trigger = audioTrigger->triggered(1);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger, audioChannel->beatDetected ? audioChannel->rms : .1f);
    }
}

void Drops::loopItem(Item &item, bool &trigger, float strength) {
    item.center.loop();
    item.center.color.fadeToBlackBy(item.decay * 5);

    item.sides.loop();
    item.sides.color.fadeToBlackBy(item.decay * 2);

    if (!item.sides.color && trigger) {
        trigger = false; 
        randomizeItem(item, strength);
    }
}

void Drops::randomizeItem(Item &item, float strength) {
    uint16_t pos = strip->randomInRange(.1, .9);
    item.center.reset()
        .setColor(CRGB::Aqua)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(15 + 100 * state->parabolicFxSpeed * strength)
        .setElasticConstant(-10)
        .setMirror(true)
        .setFill(true);
    item.sides.reset()
        .setColor(CRGB::Red)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(15 + 200 * state->parabolicFxSpeed * strength)
        .setRange(1, 1)
        .setMirror(true);
    item.decay = 2;
}
