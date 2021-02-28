#include "Scroller.h"

Scroller::Scroller(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
}

void Scroller::reset() {
    clear();
    shiftTimer = 0;
}

void Scroller::loop() {
    if (slowDown) {
        if (audioTrigger->triggered(0, .5)) {
            slowDown = false;
        }
    } else {
        if (audioTrigger->triggered()) {
            slowDown = true;
        }
    }

    uint16_t delay = slowDown ? 50 * state->linearFxSpeed : 0;

    if (shiftTimer > delay) {
        shiftTimer -= delay;
        strip->shiftUp(
            ColorFromPalette(PALETTE, audioChannel->dominantBand * 16, audioChannel->peak * 255)
        );
    }
}
