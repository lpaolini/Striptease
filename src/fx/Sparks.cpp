#include "Sparks.h"

Sparks::Sparks(Strip *strip, AudioChannel *audioChannel, State *state, CRGB centerColor, CRGB sidesColor) : Fx(strip, audioChannel, state) {
    this->centerColor = centerColor;
    this->sidesColor = sidesColor;
    audioTrigger = new AudioTrigger(audioChannel);
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].center.setup(strip);
        items[i].sides.setup(strip);
    }
}

Sparks::~Sparks() {
    delete audioTrigger;
}

void Sparks::reset() {
    clear();
    for (int i = 0; i < ITEMS; i++) {
        items[i].center.reset();
        items[i].sides.reset();
    }
    holdOffTimer.reset();
}

void Sparks::loop() {
    strip->paint(BACKGROUND_COLOR, false);

    bool trigger = audioTrigger->triggered(1);

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], trigger, audioChannel->beatDetected ? audioChannel->rms : .1f);
    }
}

void Sparks::loopItem(Item &item, bool &trigger, double strength) {
    item.center.loop();
    item.center.color.fadeToBlackBy(8);
    item.sides.loop();
    item.sides.color.fadeToBlackBy(6);

    if (trigger && !(item.center.color && item.sides.color) && holdOffTimer.isElapsed()) {
        trigger = false; 
        randomizeItem(item, strength);
        holdOffTimer.reset();
    }
}

void Sparks::randomizeItem(Item &item, double strength) {
    int16_t pos = strip->randomInRange(.2 , .8);
    double velocity = 5 + 1000 * state->parabolicFxSpeed * strength;
    item.center.reset()
        .setColor(centerColor)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(10)
        .setElasticConstant(20)
        .setCriticalDamping()
        .setShowWhenStable(true)
        .setFill(true)
        .setMirror(true);
    item.sides.reset()
        .setColor(sidesColor)
        .setPosition(pos)
        .setFixedPointPosition(pos)
        .setVelocity(velocity)
        .setElasticConstant(10)
        .setCriticalDamping()
        .setShowWhenStable(true)
        .setLowerBound(strip->first())
        .setUpperBound(strip->last())
        .setRange(4, 7)
        .setMirror(true)
        .setFill(true);
}
