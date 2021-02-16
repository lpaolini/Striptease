#include "SineMeter.h"

SineMeter::SineMeter(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    pixel.setup(strip);
    reset();
}

void SineMeter::reset() {
    clear();
    pixel.reset();
}

void SineMeter::loop() {
    if (fadeTimer > 10) {
        fadeTimer -= 10;
        strip->fade(1 + 10 * state->parabolicFxSpeed);
    }
    int pos = beatsin16(10 + 100 * state->parabolicFxSpeed, 0, strip->last());
    pixel.set(pos, ColorFromPalette(PALETTE, min(255, audioChannel->rms * 1000)));
}
