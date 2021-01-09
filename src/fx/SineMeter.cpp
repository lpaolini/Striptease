#include "SineMeter.h"

SineMeter::SineMeter(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
    pixel.setup(strip);
    reset();
}

void SineMeter::reset() {
    clear(strip);
    pixel.reset();
}

void SineMeter::loop() {
    if (fadeTimer > 10) {
        fadeTimer -= 10;
        strip->fade(1 + 10 * state->parabolicFxSpeed);
    }
    int pos = beatsin16(10 + 100 * state->parabolicFxSpeed, 0, strip->count - 1);
    pixel.set(pos, ColorFromPalette(PALETTE, min(255, audioChannel->rms * 1000)));
}
