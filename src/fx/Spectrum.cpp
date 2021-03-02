#include "Spectrum.h"

Spectrum::Spectrum(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    reset();
}

void Spectrum::reset() {
    clear();
}

void Spectrum::loop() {
    strip->fade(20);
    for (int i = 0; i < 16; i++) {
        strip->paint(i * 10, i * 10 + 7, audioChannel->bands[i].beatDetected ? CRGB::Red : CRGB::Black, true);
    }
}
