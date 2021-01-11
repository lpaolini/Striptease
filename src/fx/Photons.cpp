#include "Photons.h"

Photons::Photons(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        items[i].setup(strip);
    }
}

void Photons::resetItem(HarmonicMotion &item) {
    item.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setVelocity(MIN_SPEED + state->linearFxSpeed * random16(MAX_SPEED - MIN_SPEED))
        .setUpperBound(strip->last());
}

void Photons::reset() {
    clear(strip);
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        resetItem(items[i]);
    }
}

void Photons::loop() {
    strip->fade(30);
    bool signal = audioChannel->signalDetected;
    bool beat = audioChannel->beatDetected;
    bool trigger = (signal && beat) || (!signal && random8(100) == 0);
    uint8_t photons = MAX_CONCURRENT;

    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        if (photons && trigger && items[i].isStable()) {
            resetItem(items[i]);
            photons--;
        }
        items[i].loop();
    }
}
