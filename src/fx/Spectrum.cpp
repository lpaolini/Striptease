#include "Spectrum.h"

Spectrum::Spectrum(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    reset();
}

void Spectrum::reset() {
    clear();
}

void Spectrum::loop() {
    for (int i = 0; i < 16; i++) {
        strip->paint(i * 10, i * 10 + 7, ColorFromPalette(PALETTE, 4 * max(0, audioChannel->fftBandsSmooth[i] + 63)), false);
    }
}
