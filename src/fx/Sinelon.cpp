#include "Sinelon.h"

Sinelon::Sinelon(Strip *strip, State *state) : Fx(strip, state) {
    pixel1.setup(strip);
    pixel2.setup(strip);
    pixel3.setup(strip);
    pixel4.setup(strip);
    reset();
}

void Sinelon::reset() {
    clear();
    pixel1.reset();
    pixel2.reset();
    pixel3.reset();
    pixel4.reset();
}

void Sinelon::loop() {
    strip->fade(fade);
    uint16_t pos1 = beatsin16(freq1, 0, strip->last());
    uint16_t pos2 = beatsin16(freq2, 0, strip->last());
    uint16_t pos3 = beatsin16(freq3, 0, strip->last());
    pixel1.set((pos1 + pos2) / 2, ColorFromPalette(PALETTE, state->slowRotatingHue));
    pixel2.set((pos2 + pos3) / 2, ColorFromPalette(PALETTE, state->slowRotatingHue + 64));
    pixel3.set((pos1 + pos2 + pos3) / 3, ColorFromPalette(PALETTE, state->slowRotatingHue + 128));
    pixel4.set((pos1 + pos3) / 2, ColorFromPalette(PALETTE, state->slowRotatingHue + 192));
}
