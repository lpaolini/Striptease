#include "Photon.h"

Photon::Photon() {};

void Photon::setup(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
}

void Photon::reset() {
    color = ColorFromPalette(PALETTE, random8());
    v = MIN_SPEED + state->linearFxSpeed * float(random16((MAX_SPEED - MIN_SPEED) * 1000)) / 1000;
    t0 = millis();
    first = true;
}

void Photon::loop() {
    // Time since start
    float t = float(millis() - t0) / 1000;
    float x = v * t;

    int pos0;
    int pos1 = strip->toPosition(x);
    if (first) {
        pos0 = pos1;
        first = false;
    } else {
        pos0 = strip->toPosition(x0);
    }

    x0 = x;

    int posMin = min(pos0, pos1);
    int posMax = max(pos0, pos1);
    if (!strip->paint(posMin, posMax, color)) {
        if (audioChannel->beatDetected) {
            reset();
        }
    }
}
