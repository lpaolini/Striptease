#include "DeepSpace.h"

DeepSpace::DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < ITEMS; i++) {
        items[i].pixel.setup(strip);
    }
}

void DeepSpace::reset() {
    clear(strip);
    for (uint8_t i = 0; i < ITEMS; i++) {
        randomizeItem(items[i]);
    }
    time = 0;
}

void DeepSpace::loop() {
    strip->off();

    float dT = time / 1e6;
    time = 0;
    bool trigger = audioChannel->signalDetected
        ? audioChannel->beatDetected
        : random8() == 0;

    for (uint8_t i = 0; i < ITEMS; i++) {
        loopItem(items[i], dT, trigger);
    }
}

void DeepSpace::loopItem(Item &item, float dT, bool &trigger) {
    item.y += v * dT;
    if (item.y < 0) {
        randomizeItem(item);
    } 
    if (item.visible) {
        float angle = atan2f(item.y, item.x);
        float distanceSquared = powf(item.x, 2) + powf(item.y, 2);
        float pos = 1 - (angle / HALF_PI);
        uint8_t brightness = min(255, 10 * MAX_SQUARE_DISTANCE / distanceSquared);

        // if (trigger && item.type == BLUE && item.y < (MAX_Y_DISTANCE + MIN_Y_DISTANCE) / 2) {
        if (trigger && item.type == BLUE && item.y < MAX_MUTATION_Y_DISTANCE && item.x < MAX_MUTATION_X_DISTANCE) {
            trigger = false;
            item.type = RED;
        }

        CRGB color;
        switch (item.type) {
            case BLUE:
                color = CHSV(160, 255, brightness);
                break;
            case RED:
                color = CHSV(0, 255, brightness);
                break;
            default:
                color = CRGB::Black;
                break;
        }

        item.pixel.setNormalized(pos, color);
    }
}

void DeepSpace::randomizeItem(Item &item) {
    item.x = random(MIN_X_DISTANCE, MAX_X_DISTANCE);
    item.y = random(MIN_Y_DISTANCE, MAX_Y_DISTANCE);
    item.type = random(100) < 100 * state->parabolicFxSpeed ? BLUE : HIDDEN;
    // item.hue = 160;
    // item.hue = random(100) == 0 ? 0 : 160;
    item.pixel.reset();
    // item.visible = random(100) < 100 * state->parabolicFxSpeed;
    item.visible = true;
}
