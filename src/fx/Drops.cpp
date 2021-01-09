#include "Drops.h"

Drops::Drops(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    items = new Item[ITEMS];
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].center.setup(strip);
        items[i].sides.setup(strip);
    }
}

Drops::~Drops() {
    delete[] items;
}

void Drops::reset() {
    clear(strip);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].center.reset();
        items[i].sides.reset();
    }
}

void Drops::loop() {
    *(strip->leds) = BACKGROUND_COLOR;

    bool signal = audioChannel->signalDetected;
    bool beat = audioChannel->beatDetected;
    bool reset = (signal && beat) || (!signal && random8(100) == 0);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], reset, beat ? audioChannel->rms : .1f);
    }
}

void Drops::loopItem(Item &item, bool &reset, float strength) {
    item.center.loop();
    item.center.color.fadeToBlackBy(item.decay * 5);

    item.sides.loop();
    item.sides.color.fadeToBlackBy(item.decay * 2);

    if (!item.sides.color && reset) {
        reset = false; 
        randomizeItem(item, strength);
    }
}

void Drops::randomizeItem(Item &item, float strength) {
    uint16_t pos = strip->randomPosRange(.1, .9);
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
