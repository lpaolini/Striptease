#include "Scroller.h"

Scroller::Scroller(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    reset();
}

void Scroller::reset() {
    clear(strip);
    shiftTimer = 0;
}

void Scroller::loop() {
    unsigned int delay = 10 + 20 * (1 - state->linearFxSpeed);
    if (shiftTimer > delay) {
        shiftTimer -= delay;
        strip->shiftUp();
        (*(strip->leds))[0] = ColorFromPalette(PALETTE, audioChannel->peak * 255, audioChannel->peak * 255);
    }
}
