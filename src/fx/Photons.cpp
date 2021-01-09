#include "Photons.h"

Photons::Photons(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        photons[i].setup(strip, audioChannel, state);
    }
    reset();
}

void Photons::reset() {
    clear(strip);
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        photons[i].reset();
    }
}

void Photons::loop() {
    strip->leds->fadeToBlackBy(30);
    for (uint8_t i = 0; i < NUM_PHOTONS; i++) {
        photons[i].loop();    
    }
}
