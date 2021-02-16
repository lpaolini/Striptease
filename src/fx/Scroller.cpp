#include "Scroller.h"

Scroller::Scroller(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    reset();
}

void Scroller::reset() {
    clear();
    shiftTimer = 0;
}

void Scroller::loop() {
    unsigned int delay = 10 + 20 * (1 - state->linearFxSpeed);
    if (shiftTimer > delay) {
        shiftTimer -= delay;
        strip->shiftUp(ColorFromPalette(PALETTE, audioChannel->peak * 255, audioChannel->peak * 255));
    }
}
