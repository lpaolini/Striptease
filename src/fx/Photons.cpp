#include "Photons.h"

Photons::Photons(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        items[i].setup(strip);
    }
}

Photons::~Photons() {
    delete audioTrigger;
}

void Photons::resetItem(HarmonicMotion &item) {
    item.reset()
        .setColor(ColorFromPalette(PALETTE, random8()))
        .setVelocity(MIN_SPEED + state->linearFxSpeed * random16(MAX_SPEED - MIN_SPEED))
        .setUpperBound(strip->last());
}

void Photons::reset() {
    clear();
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        resetItem(items[i]);
    }
    audioTrigger->reset();
}

void Photons::loop() {
    strip->fade(30);
    bool trigger = audioTrigger->triggered(1);

    uint8_t photons = MAX_CONCURRENT;

    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        if (photons && trigger && items[i].isStable()) {
            resetItem(items[i]);
            photons--;
        }
        items[i].loop();
    }
}
